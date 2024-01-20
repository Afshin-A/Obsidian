# IAM
Identity and Access Management - service that allows admins control authorization and authentication

Identity Federation - this is when you sign in to a website (for example) using your credentials of another website because the two websites have a partnership for authenticating users.

Note: Don't sign in as root user for everyday tasks. Use the principle of least privilege: i.e. create a user with the least number of privileges needed to do the job.

The root has access to everything

A **Policy** is usually a JSON object attached to identities (IAM users or groups) or resources in the system. It defines their permissions, setting who can access what.

**Principal** refers toaccount members, users, or roles