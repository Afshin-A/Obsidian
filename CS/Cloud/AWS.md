Downloading the AWS CLI .msi installer for windows is not enough to access the aws CLI in CMD. I also had to add the folder located in `C:\Program Files\Amazon\AWSCLIV2` to the `Path` environment variable 

```powershell
aws configure
```
This will prompt for user credentials, 

To ensure it worked,
```powershell
aws sts get-caller-identity
```

Set a custom name for the AWS account in CLI:
```powershell
aws configure --profile dev-account
```




Temporarily add env variables for the current terminal session. **Confirmed: this worked!**
```powershell
$env:AWS_ACCESS_KEY_ID="AKIA..."
$env:AWS_SECRET_ACCESS_KEY="wJalr..."
```

Permanently add env variables to the system. ==This adds the variables under the **user** env variables in windows==
```powershell
setx AWS_ACCESS_KEY_ID "AKIA..."
setx AWS_SECRET_ACCESS_KEY "wJalr..."
```


# Identity vs Resource Based Policies

Who can do what, to which resource, under what conditions?
### Resource based policies
These are directly attached to a resource (e.g. SQS). 
They require the `Principal` element—the who part. The resource needs to state which identities are allowed to access it.

```python title:"Inline policy example for AWS KMS key resource" hl:'principal'
resource "aws_kms_key" "key" {
	description             = "Key used for encrypting data at rest in SQS"
	enable_key_rotation     = true
	policy                  = jsonencode({ 
		sid = "EnableIAMUserPermissions" 
		actions = ["kms:*"]                          # what can they do?
		resources = ["*"]                            # what can they access?
		principals = [{                              # who are they?
			type = "AWS" 
			identifiers = ["arn:aws:iam::${data.aws_caller_identity.current.account_id}:root"] 
		}]
		... 
	})
```

### Identity based policies
Identity based policies don't need the `Principal` element. 
Just like resource based policies, the policy statement is defined inside a `data aws_iam_policy_document` block.
This is then used to form an `aws_iam_policy` resource, which is then attached to a user.

Both types share the data `aws_iam_policy_document` block. So maybe this could be its own module that exports the statement as json

