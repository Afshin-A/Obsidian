### Benefits of Kafka


### When to use Kafka



### How does Kafka work?

*producers* sends an *event* to Kafka in a fire-and-forget manner
Event contains a key, value, timestamp, and optional metadata

Kafka groups similar events into a *topic*, which is an ordered queue that stores events in non-volatile memory until they're processed by the *consumers*. 
It is the engineer's responsibility to create topics and decide what events go to what topic.
Consumers *subscribe* to the topics. 
Consumers can do something with the event, then create a new event and pass it into another topic, which is then used by another consumer, and so on. So we can create this sort-of chain effect with our events, where one event causes a chain of events that follow up (so consumers can also act as producers). All the while, we're avoiding coupling processes. We're not jamming them into one big function/service. Instead, we're separating them by putting a topic between them. They're independent. 

*Brokers* are kafka servers where data from the topics is physically stored
There can be multiple brokers that store data replicas to provide fault tolerance
We can set up a retention policy to configure how long after an event has been processed they stay in the brokers.

Can be used for streaming real-time analytics data, where data is continuously pushed into topics and processed by consumers. There can be thousands of producers and consumers with millions of events. How does Kafka scale up? Using *Partitions*
Producers can write into multiple partitions at the same time

As for how the consumers keep up, we can create them as containers. Serverless service will automatically create more instances. These will be grouped up together and identified by a `groupId` attribute. That's how Kafka will know how and where to distribute traffic.
#### Terminology
- Topic
- Group-id
- 

### Example Code
Start by installing the Kafka library:
```
npm install kafkajs
```

First, we need to configure Kafka:
```ts
import { Kafka, KafkaConfig } from 'kafkajs';
const kafkaConfig: KafkaConfig = {
	clientId: '',
	brokers: ['localhost:9092'],
};

const kafka = new Kafka(kafkaConfig);
```

Next, we need to create a producer:
```ts
const producer = kafka.producer();
const runProducer = async () => {
	await producer.connect(); // what are we connecting to exactly?
	
	await producer.send({
		topic: 'test-topic',
		messages: [
			{value: '', key: ''},
		]
	});
	
	await producer.disconnect();
};

runProducer.catch(console.error);

```

Finally, we need to create a consumer:
```ts
const consumer = kafka.consumer({ groupId: 'test-group' });
const runConsumer = async () => {
	await consumer.connect();
	
	await consumer.subscribe({ topic: 'test-topic', fromBeginning: true });
	
	const eachMessageLambda = async ({topic, partition, message}) => {
		console.log({
			partition,
			offset: message.offset,
			value: message.value?.toString()
		});
	};
	
	await consumer.run({
		eachMessage: eachMessageLambda
	})
};

runConsumer().catch(console.error);
```