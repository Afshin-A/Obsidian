# Docker Compose
In my post last week, I explained the benefits of containerization, including managing multi-component software such as MEAN stack web applications. Suppose we're resuming work on such a project at a new company. There are two ways to run the application.
1. Individually running and configuring the containers

docker run -d --name=angular -p 5000:4200 --link express:express angular
docker run -d --name=express express
docker run -d --name=mongodb mongo

All containers in the project must be set up correctly. For instance, because containers may depend on one another, we need to start them at a specific order. In addition, every software engineer will have to enter these commands into the terminal every time they want to start the application. Now imagine the redundancy and complication of this task if there were dozens of containers
2. Docker compose

The easier way is to use Docker compose. This tool allows us to manage the run process by organizing all instructions and commands in a compose.yml file. This file can be shipped with the software and distributed to the users. There are 3 versions of docker compose. However, for simplicity, we use version 1 to rewrite the commands from the example above:

express:
	image: express
mongo:
	image: mongo
angular:
	image: angular
	links:
		- express # shortway for writing express:express
	ports:
		- 5000:4200

To run the application, we first navigate to the root directory of the project and enter the following command:

docker compose up


This will create and start all containers in our project.


# Compare Local and Cloud Storage
Data is an integral part of any application, if not the most important. When it comes to storing application data, we own and run our own data center. This method is expensive. Consider the cost of the necessary hardware (servers, hard drives), power, housing, etc. It also requires high maintenance, as we need to hire a team dedicated to physically maintaining the data center by replacing failed drives, for example, or responding to malicious attacks.

As you can see, this method of storing data is not ideal for, even if we can overcome these challenges, we cannot easily scale our application because our data needs, depending on the application, will keep growing. Therefore, instead of storing data locally, we can rent a cloud service such as S3 from AWS. We no longer are concerned about maintaining a data center. We can safely store encrypted data and easily access it over a network connection anytime as needed. It is cheaper to use S3 because we only pay for the storage we use. This also makes it easy to scale our application. Furthermore, S3 makes it possible for developers to work in teams. For example, security policies allow for defining roles within an organization, assigning read/write privileges based on those roles. One unique feature of S3 is that it automatically creates backups throughout different facilities spread all around the world, so we no longer need to worry about losing important data.

# Lambda
Hello class, in this post, I'm going to make a quick comparison between AWS Lambda and EC2 for hosting web services online.

Lambda is a serverless service offered by AWS. With Lambda, we do not manage servers necessary to run our application. Instead, after minor configurations (such as the programming language, events, and of course the code), AWS will automatically handle everything for us, from assigning the necessary resources, to scaling whenever necessary. It's important to note that Lambda is a pay-as-you-go service: you only pay for the resources you need.

EC2, on the other hand, is basically a virtual machine hosted on the cloud. We're essentially renting a server, so we are responsible for configuring it (by setting the resources such as processing cores, RAM, storage, firewall, etc) and providing maintenance. Consequently, the renting costs are fixed for a duration of time.

# Mongo Vs Dynamo
MongoDB and DynamoDB are both NoSQL database management systems, offering flexible, schemaless solutions for a variety of applications. DynamoDB is a cloud service provided by AWS, making integration with other AWS services easy, but it also ties your application to AWS, making it difficult to transition to another platform. In contrast, MongoDB is a cross-platform database that can be deployed anywhere, including on various cloud services. In fact, MongoDB can be used in a serverless manner through MongoDB Atlas.

MongoDB is more flexible than DynamoDB. With MongoDB, you can store anything in JSON-format documents, allowing the data model in your application to evolve over time depending on the application's needs. Additionally, MongoDB has built-in checks that can reject incorrect data. In contrast, DynamoDB only supports a handful of data types and relies more on the application to interpret the data and verify its integrity. Another difference between the two is in querying data. MongoDB supports indexing, which makes efficient queries possible, allowing you to query based on multiple fields and sort the results in a certain order. DynamoDB, on the other hand, is primarily a key-value store and has more limited querying capabilities since it uses a primary key (and sometimes a secondary key) for item look-up.

DynamoDB is highly available and durable. It offers the same level of protection as AWS S3 since it automatically replicates data across different availability zones. It also takes care of maintenance, backups, and scaling automatically, so there's no need to worry about software updates, for example. DynamoDB is ideal for applications with unpredictable workloads because it imposes no limits on storage. MongoDB, while also scalable, requires careful planning upfront to account for horizontal scaling of servers and efficient indexing of the database.

# IAM policies and security
Suppose we are working at a large company with hundreds of employees. Within any organization, there is a structure of hierarchical roles: employee, manager, CEO, etc.. Therefore, we would want to specify the access privileges each role has. IAM is an amazon service that allows us to define roles and policies that dictate what AWS resources those roles can access. We obviously don't want to give everyone access to crucial data and configurations. For security purposes, we want to give each user the minimum access privileges they need to perform their work, also known as the least privilege principle. IAM roles aren't restricted to human users. They can also be assigned to other AWS resources. For example, you can allow an EC2 instance to access data from certain S3 buckets.

For this course, we were granted limited access to AWS through a controlled environment through the "LabRole" role. I would often receive errors when working with my lambdas or the API gateway that my role didn't have sufficient privilege to perform a certain action.



# Presentation
## Introduction
Hello. My name is Afshin. I am a student at SNHU. I am making this presentation for my Full Stack Development course (CS470).
In the following slides, we're going to discuss the process and challenges of migrating and adapting a MEAN stack web application to the serverless architecture on the AWS cloud environment
this way, our application is available, flexible, and scalable
we don't have to worry about loss of data, as AWS creates several copies of the data in different data centers

Angular app is hosted on **S3**, which makes it highly scalable and eliminates the need for traditional web servers.
the front-end to an **API Gateway**, which acts as a secure entry point for your APIs. API Gateway offers features like request validation, throttling, and usage plans to handle load efficiently.
**AWS Lambda** functions, written in node.js, to handle each HTTP request means that your application is event-driven and fully scalable. You only pay for the actual compute time, which is a major cost-saver for applications with variable loads.
By using **DynamoDB**, you're leveraging a **NoSQL, managed database service**. DynamoDB scales automatically and has built-in high availability. It's ideal for applications with unpredictable traffic because you only pay for the requests and data storage used.
This serverless model is excellent for applications with **dynamic workloads**, where scaling, availability, and cost optimization are critical.

- **User Interaction**: A user interacts with the Angular front-end hosted on S3.
- **API Requests**: When the user performs an action (e.g., creating a new record), Angular sends an HTTP request via **API Gateway**.
- **Lambda Execution**: The API Gateway triggers the appropriate Lambda function based on the HTTP method (e.g., GET, POST, PUT, DELETE).
- **Database Interaction**: Lambda functions communicate with DynamoDB to store or retrieve data.
- **Response**: The Lambda function returns the appropriate response to the API Gateway, which then forwards it to the frontend.



## Containerization and Orchestration


and we do this by using Docker Compose. What is docker compose?


just about anything can be containerized. And why shouldn't it be that way? After all, you can ship your software with all of its dependencies ready to use. A user will only have to enter a few commands to run the application. This solves the infamous "but it runs on my machine" problem. As an example, suppose you are a new developer on a team working on a complex project. To start, you have to setup your environment, download software, install dependencies, and so on. With containers, you just need to install the docker engine and  run the image your company has published. It's completely isolated, as far as the image is aware, and has its own operating system and file system, 

Containers are great for component-based software, including the MEAN stack web app. The components of such applications might have conflicting requirements, such as different versions of a dependency. This is referred to as the matrix of hell. We can solve this problem by running each component of the application from its own container to ensure that no compatibility issues arise in the future. This is possible because docker containers are isolated systems.

Containerization also facilitates deploying applications onto cloud services. Firstly, we don't need to worry about setting up the running environment. In addition, docker containers make it easy to scale applications horizontally because we can deploy as many instances of a docker image as we need. Docker orchestration tools like Kubernetes allow provide solutions to easily manage containers. These are tools and scripts that automatically deploy an additional instances of a container when, for example, the load is too high, or when we need to replace a container that has failed, or even when the host server crashes. It also manages advanced networking between containers, even across different hosts (or nodes) in the cluster.

If you're working on a large project with many components, multiple containers, then All containers in the project must be set up correctly. For instance, because containers may depend on one another, we need to start them at a specific order. In addition, every software engineer will have to enter these commands into the terminal every time they want to start the application. Now imagine the redundancy and complication of this task if there were dozens of containers.  Docker compose. This tool allows us to manage the run process by organizing all instructions and commands in a compose.yml file. This file can be shipped with the software and distributed to the users. 


Lambda needs to know the runtime environment, what to run, and when
Lambda follows event driven programming. so it listens for when an api call is made to run. the api knows what to run because the lambda exports a handler function

API gateway maps incoming API calls to a service to handle the API call. it will receive a REST API request, forward that request to the correct Lambda function, and manage returning the result. It will also act as our security barrier between the outside world and our Lambdas. The outside world will only be able to access the APIs we deploy, and the API Gateway will be the only service with permissions to call our Lambdas.


