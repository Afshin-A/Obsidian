Terraform uses the *HashiCorp Configuration Language* (HCL) to configure and provision cloud resources from various providers.
*HashiCorp* is the name of the company behind Terraform.

We provision an EC2 (with an Amazon Linux OS) instance on AWS to run our experiments with Terraform.
For that, we have to manually go to the AWS dashboard and create this an EC2 instance. AWS will give you a similar command as the following so you can log in via SSH console:
```bash
ssh -i "LearnTerraformCredential.pem" ec2-user@ec2-18-117-89-225.us-east-2.compute.amazonaws.com
```
**It's important to log out with the `logout` command in bash, or manually from the AWS dashboard, else the EC2 instance will keep running and incurring costs.** 

After logging in, we can install Terraform using the command prompt.
https://developer.hashicorp.com/terraform/install

We can install it locally, or on the EC2 instance.
There is also an official VS Code extension that adds support for the HCL language 
### Authentication in Terraform
The AWS provider that Terraform uses needs two values to authenticate and authorize creation of AWS resources. These are:
 - *AWS_ACCESS_KEY_ID*, aka access key id. This can be public.
 - *AWS_SECRET_ACCESS_KEY*, the secret key. **This should absolutely be private,**

It is not recommended to put credentials directly in a Terraform script. So instead, we use environmental variables
On our ES2 instance, we can temporarily set credentials via SSH:
```bash
export AWS_ACCESS_KEY_ID=key_id_value
export AWS_SECRET_ACCESS_KEY=secret_access_key_value
```
In we're running Terraform on our local windows machine, we can add these to the system variables in windows.
The name of the keys must be exactly as written. 
When we run `terraform apply`, the AWS provider automatically looks in the system environmental variables.
### Terraform Commands
Terraform scripts are written in `.tf` files
**Note: Must call all these commands from the terraform dir**
```bash
terraform init # Initializes the script by installing dependencies for working with the provider
terraform fmt --recursive # Short for format. Optional. Applies spacing format 
terraform validate # Optional. Checks syntax
terraform plan # Creates a plan that for-shadows all changes that this script will make. You can save this plan by running terraform plan -out="file.tfplan"
terraform apply # Executes the script. Bypass confirmation by running terraform apply --auto-approve
terraform destroy # destroys all resources created by terraform apply
terraform output -json dir # outputs the output variable values, optionally to json file
terraform show # since the plan shows the plan
```
### A few Linux commands that may come in handy
Refer to [[Bash Tips]] for more useful Linux commands

Display the contents of a file:
 ```bash
cat main.tf
```

Downloading a file via SSH
Using the *secure copy protocol* (scp) to download the main.tf file from EC2 instance to my local machine First make sure you're logged out. That is, the command is running on your machine, not the server.  
 ```bash
 scp -i "LearnTerraformCredential.pem" ec2-user@ec2-18-117-89-225.us-east-2.compute.amazonaws.com:/home/ec2-user/01-tf-ec2/main.tf ~/Downloads/Terraform
```

Create files without opening them
 ```shell
 touch main.tf file1.txt
 ```
### What a terraform script looks like
```json
// main.tf
provider "aws" {
  region = "us-east-2"
}
resource "aws_instance" "linux-vm" {
  count           = 1
  ami             = "ami-0ca4d5db4872d0c28"
  instance_type   = "t3.micro"
  key_name        = "LearnTerraformCredential"
  security_groups = ["default"]
  tags = {
    Name = "TerraformVM"
  }
}
```

We might want the EC2 VM instance to run some commands after it's been created. 
We use the `user_data` key. 
You can either import the commands from a file or list them directly inside the Terraform script.
```json
resource "aws_instance" "linux-vm" {
  count           = 1
  ...
  user_date = file("installHttpd.sh")
  ...
}
```

The `installHttpd.sh` is a shell script file. It could maybe look like this:
```sh
#! /bin/bash
sudo su
yum install httpd -y
cd /var/ww/html
echo "<html><h1>Hello World!</h1></html>" > index.html
service httpd start
```
But we must first change the permissions of the bash file using `chmod u+x ./installHttpd.sh` so it can be executed on the machine
### Terraform State Files
Running the command `terraform apply` creates a file named `terraform.tfstate`; it's basically a JSON file that contains all the information about the infrastructure created. It defines what the infrastructure should look like. It contains sensitive information, so *it should not be committed to version control.* However, it's important this file be shared between all developers. 
Let's say developer A makes some changes to the infrastructure. Developer B wants to make changes on top of A's changes. So developer B needs the `terraform.tfstate` file to plan out his changes. `terraform.tfstate` is the representation of the infrastructure in the form of a file. It needs to be shared between everyone in the devops team.

We use an Amazon S3 bucket to store the state file. It's secure, cheap, and has IAM integration so we can control who can access the state file. This is done by adding a `terraform` block in the main script (parent component). Inside the `terraform` block, we use a `backend` block that defines info about the s3 bucket we'll be using to store  
```json
terraform {
  backend "s3" {
    bucket         = "my-terraform-state-bucket"
    key            = "path/to/my/state/file.tfstate"
    region         = "us-east-1"
    encrypt        = true
    // S3 has native statelocking feature. this is the modern approach
    use_lockfile = true
    // you can also use a dynamodb table? but I couldn't make it work. I believe we have to create a dynamodb table named terraform-state-locking first
    // dynamodb_table = "terraform-state-locking"
  }
}
```
This also does what's called *state-locking*, which prevents multiple people from making changes to this file at the same time, avoiding file corruption and such.

The command `terraform destroy` uses the `terraform.tfstate` file to delete the created resources.  
The `terraform.tfstate` will also prevent you from accidentally running `apply` and creating duplicate resources from the same configuration we have in `main.tf`. It's also used to destroy the resources. **Do not delete/move this file.**
### Input Variables in Terraform
Variables allow us to make the Terraform script more modular and reusable. We can import information dynamically into Terraform scripts via variables.

First, we must define the variables:
```json
// vars.tf (filename)
variable "ami" {
    description = ""
    default = "ami-0ca4d5db4872d0c28"
}
variable "instance_type" {
    description = ""
    default = "t3.micro"
}
```
The variables are given a default value here.
But we can also assign them arbitrary values, which must be defined in a file that strictly follows the following naming format:
- `terraform.tfvars` -- must be named exactly as is
- `terraform.tfvars.json` -- must be named exactly as it
- `placeholder.auto.tfvars` -- "placeholder" can be changed to anything, including "staging" or "prod", etc..
- `placeholder.auto.tfvars.json` 
Variable assignment inside these files may look like:
```json
ami_id = "ami-0c55b159cbfafe1f0"
instance_type = "t2.micro" 
```

We can then use the variables in the script files like this:
```json
// main.ts
resource "aws_instance" "linux-vm" {
  count           = 1
  ami             = "${var.ami}" 
  instance_type   = "${var.instance_type}"
  ...
}
```
This method allows for string manipulating.

**Note:** We can also write variables without the curly braces like this:
```json
ami = var.ami
```
### Output Variables
Some important information about our AWS resources, like public or private IP addresses, is not known until after they are created--after we call `terraform apply`. Nevertheless, we can define output variables that capture these values and output them to other parts of the Terraform infrastructure or out onto the console.
An output variable is defined like this:
```json
// output.tf
output "output_var_name" {
	value = resource_name.alias.key 
}
``` 
And we can use it as follows:
```js
...

resource "aws_instance" "app_server" {
  ami           = "${var.ami_id}"
  instance_type = "${var.instance_type}"
  tags = {
    Name = "ChildModuleInstance"
  }
}

output "public_ip" {
  description = "The public IP address of the EC2 instance."
  value       = aws_instance.app_server.public_ip
}
```

More about how the output variables can in used in other components in the following sections
### Modules and Organization in Terraform
The idea is to create a reusable component (a script file) for each resource we want to create. These are *child components*. They're standalone and could very well create a resource. 
However, child components are imported into a *root* (aka *parent*) *component*. This component is responsible for creating the infrastructure as a whole.


We don't need to explicitly import variable definition files or variable value files into the scripts, because Terraform basically runs all files that end with `.tf` and the `.tfvar` variations.

The proposed folder structure is as follows:
```
├── . 
├── main.tf          # Parent module's configuration 
├── provider.tf      # Contains information about the provider
├── variables.tf     # Parent module's variable declarations 
├── terraform.tfvars # Assign values to variables
├── modules/ 
│   └── ec2-instance/    # Child module's directory 
│       ├── main.tf      # Child module's configuration 
│       ├── variables.tf # Child module's variable declarations 
│       └── outputs.tf   # Child module's output declarations
|   └── rds-instance/    # Child module's directory 
│       ├── ...
│
```
Each module should have its own input and output variable declaration files, variable assignment (e.g. `.tfvars` and such) file, and the script for creating a resource. 


Child components are used in the parent component as follows: 
```json
// main.ts
// Define a variable for the VPC ID that will be used by both modules
variable "vpc_id" {
  description = "The VPC ID to deploy resources into."
  type        = string
}

// Module to create a Security Group
module "database" {
  source = "./modules/security-group"
  vpc_id = var.vpc_id
}

// Module to create an EC2 Instance
module "web_server" {
  source = "./modules/ec2-instance"
  ami_id        = var.ami
  instance_type = var.instance_type
  // output variable of the security module, which is another child component, is used here
  security_group_id = module.web_security_group.security_group_id
}

// Output the public IP of the web server
output "web_server_ip" {
  description = "The public IP address of the web server."
  value       = module.web_server.public_ip
}
```


variables are defined at module level
variables are again defined in root level. 
variables are assigned value at root level
when creating modules, values are assigned from the root. 
this is to keep modules reusable. if we also create a `terraform.tfvars` file at module level, then we're essentially hard coding values. we can't reuse the module with different values later. that's why we must set the values at the root level

for output variables, the child modules designate them in a special syntax:
```js
output "instance_public_ip" { 
	description = "..." 
	value = aws_instance.app_server.public_ip 
}
```
The root component will again define an out variable 
```js
output "web_server_ip_address" {
	 description = "..."
	  value = module.web_server.instance_public_ip
}
```
this will be printed in the console
So basically output variable moves up like this:
child -> parent -> console

When the parent is setting up a child component, it can use output variables from another child component. For example, let's say we wanted to make sure all the resources shared the same security group. Then the parent component will configure all resources to use that value from a component that is responsible for that variable and exports it.
```js
security_group_id = module.web_server.security_group_id
```
These assignments are done at the root level. This is important.
### Tainted
**Note:** The taint command has been deprecated. Instead we now use the following:
```bash
terraform apply -replace="aws_instance.linux-vm" --auto-approve
```

<hr>

As we discussed in the [[Terraform#Terraform State Files| section for Terraform state files]], we cannot use the same script to create duplicate resources. In other words, you cannot apply the same script twice. 
So if we want to recreate a resource for whatever reason (e.g. there was an issue with the provider), we would have to destroy the resource and apply the script again.

However, there is a more straight forward way: we can mark a resource as *tainted*:
```
terraform taint resource_name.alias
```
Example:
```bash
terraform taint aws_instance.linux-vm
```
Running `terraform apply` again will recreate this resource.

We can go cancel that by un-tainting a resource:
```shell
terraform taint aws_instance.linux-vm
```


### Using AWS Secret Manager with Terraform
```ts
// in main.tf
data "aws_secretsmanager_secret_version" "db_password" {
  secret_id = "prod/database/password"
}

module "app_database" {
  source = "./modules/rds-instance"
  password = data.aws_secretsmanager_secret_version.db_password.secret_string
  ...
}
```
- We fetch a secret from the AWS secret manager using the `data` block, a built in feature into Terraform that grabs the secret at run time.
- We tell terraform where to get the data from: `"aws_secretsmanager_secret_version"`. `db_passsword` is the alias
- We then tell terraform what secret to grab:   `secret_id = "prod/database/password"` using the name we gave the secret. (In this case it's  `prod/database/password`). 
- The data block will have a `secret_string` attribute, to access it, we use the same syntax as if we were retrieving an output variable from a module, but it's a little different:
 ```js
data.aws_secretsmanager_secret_version.db_password.secret_string
```

### Meta-data arguments
#### `count`
We've seen this keyword in [[Terraform#What a terraform script looks like|examples]] before.
Terraform will create duplicate copies of a resource. 
```js
resource "aws_instance" "web_server" {
  count         = 3
  instance_type = "t2.micro"
  ami           = "ami-0c55b159cbfafe1f0"
  tags = {
    Name = "web-server-${count.index}"
  }
}
```
We can use the array notation to access each instance. For example,
```js
aws_instance.web_server[0]
aws_instance.web_server[1]
aws_instance.web_server[2]
```
#### `for_each` 
This is a more advanced way of creating duplicate resources. Think of it as a for loop that goes through a map. It creates a resource for each key-value pair.

First we define the map variable:
```js
variable "server_types" {
  type = map(string)
  default = {
    staging = "t2.micro"
    prod    = "t3.medium"
  }
}
```

```js
resource "aws_instance" "app_server" {
  for_each      = var.server_types
  instance_type = each.value
  ami           = "ami-0c55b159cbfafe1f0"
  tags = {
    Name = "${each.key}-server"
  }
}
```

### Terraform in CI/CD

1. Developer makes changes in `.tf` files
2. Developer pushes changes to GitHub
3. Push triggers CI/CD pipeline
4. This will run the terraform script
    1.  Authenticates to AWS using secure credentials, not local ones.        
    2. Runs `terraform init` to connect to the remote backend (your S3 bucket).
    3. Fetches the latest state file and locks it.
    4. Generates a plan based on the new code.
    5. Attaches the plan to the pull request for review.
5. The plan is reviewed by another team member. They can see exactly what changes will be made before anything is deployed.
6. After approval, another job will run `terraform apply` and apply the changes.


### Media and References

<center><iframe width="560" height="315" src="https://www.youtube.com/embed/wAwVOFf0Xq4?si=yGEPioRTzX2FDowg" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe></center>

