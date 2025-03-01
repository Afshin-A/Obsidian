
# On Site
## On premise deployment
We own and run our own data center. Expensive (cost of the machines, electricity, housing) high maintenance (hire people to physically taking care of the servers, replacing failed drive, physically securing them)
we cannot predict how much our application will grow in the future
keeping backups of important data adds to space limitations

We can rent a server from a cloud provider like AWS. it is safe and secure through the use of encryption. also, security policies allow us to define roles within our organization and assign read/write privileges  
and can easily be accessible over a network connection, anytime as needed. allows us to easily  scale our application. amazon S3 automatically creates backups in different facilities throughout the world to minimize latency
you can create different versions of your data and keep track of them
pay as you go, for the storage you use
storage classes are designed for different use cases for further optimization. so for example, data that is frequently used can be accessed more easily
# IaaS/CaaS
## Infrastructure as a service (IaaS)
We can rent a server from a cloud provider like AWS. A server would be virtual machine and an operating system. We can sometimes provide our own OS image for the VM. AWS also provides their own OS images are called amazon machine images (AMI). 
Pay for the resources you use

## Containers as a service (CaaS)
We run docker container images instead of OS images, hence taking advantage of all the benefits of containerization.
AWS offers ECS and Fargate

# PaaS/Serverless
## Platform as a service (PaaS)
We focus on software development instead of the minutiae of how and where it is hosted. The platform will configure most of the server settings. But we still have to determine how much memory or processing power we want to use. 

## Serverless
Serverless - "someone else's server"
cloud provider determines the platform and how to run the code, and handles resources.
It is highly scalable, and it is event driven. I'm guessing that means resources are allocated or freed in response to, for example, API calls. 
AWS lambda serverless compute model, DynamoDB serverless NoSQL database

# Software as a service (SaaS)
Cloud hosted software ready to use 
license fee



Amazon S3
Amazon Simple Storage Service 


# AWS API Gateway and Lambda
## Architecture
![[Pasted image 20240926102940.png]]
