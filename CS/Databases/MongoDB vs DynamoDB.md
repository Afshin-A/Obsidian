Both are NoSQL database management systems. Both are flexible and do not require to compile a schema. dynamo is a cloud service provided by AWS, it makes integration easy with other AWS services, but it also ties your application to AWS and makes it difficult to transition to another platform. In contrast, mongodb is a cross-platform application that can be deployed anywhere, including on the clouds. In fact, MongoDB can be used in a serverless manner thanks to MongoDB Atlas.



Mongo is document-oriented, where each JSON object can store any kind of data.
Dynamo uses hashed keys to lookup data in the table



Mongo is flexible, you can store anything you want in the documents, so the data model can easily evolve over time depending on the needs of the application
Mongo allows for efficient queries thanks to indexing. You can create indexes that can be based on multiple elements within the documents
scaling mongodb horizontally requires careful planning. so you need to architect your application from the start 

Dynamo can be easily paired with other AWS services. it is highly available and durable. In fact, it offers the same protection as S3, since it automatically replicates data across different availability zones. Automatically takes care of maintenance and backup, and scaling (?). Plus, we do not need to worry about updating the software for example
Dynamo is ideal for applications with unpredictable workloads because it does not impose a limit on storage 

