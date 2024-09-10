Docker solves the infamous problem of "Well, it runs on my machine". Imagine that you are a new developer on a team working on a complex problem. Before anything, you have to setup your environment, download software, and install dependencies. With containers, you just download and run the image the company has created. 

A **container** is a running instance of a docker **image**. An image is like a blueprint. A container is a process.
Containers are isolated (although not entirely as virtual machines are). Each container contains all the necessary dependencies and software that is necessary to run a software. Let's say you want to run the MEAN stack. These components might have conflicting requirements. For example, one may need this version of a dependency, while the other needs a different version of the same dependency. So solve this problem, also referred to as **matrix of hell**, we would run each component of the stack from its own container to ensure no compatibility issues arise in the future.

An operating system is consisted of a kernel, which directly communicates with the underlying hardware, and software (such as drivers) that run on top of the kernel. Different operating systems have different kernels (so different architectures, compilation process, etc) and are not cross compatible. When you run a docker image that was made for a Linux system, for example, we need to run it on a Linux host. We can run Linux images that use different distributions (such as ubuntu, fedora, etc.) on the same Linux machine because they use the same kernel. But to run a Windows image on a Linux system, we would have to use a virtual machine.

A virtual machine is layered. First you have the hardware, then the hypervisor, and then virtual machines placed horizontally on top. Each virtual machine runs its own operating system. Each VM will then run docker and as many containers as needed. One advantage of this method is that each virtual OS is completely isolated. But this method is resource intensive. OS images are gigabytes big.

Docker containers are stateless. So when they're stopped, all data is lost.

You can containerize just about anything. It makes installation very easy. Uninstalling a container is as easy as removing it. This makes cleaning up so easy.

You can deploy multiple instances of your application for horizontal scaling.
Docker makes it easy to scale your application because we can just deploy multiple instances of our image.
# Commands
Before anything, make sure the docker desktop application (we're using Windows) is running.

**All of the following commands should be preceded with `docker`.** So `run` becomes `docker run`.

| Command                                       | Action                                                                        | Example                                           |
| --------------------------------------------- | ----------------------------------------------------------------------------- | ------------------------------------------------- |
| pull                                          | Pull an image to your local environment                                       |                                                   |
| run image-name                                | Runs an image                                                                 | docker run ubuntu                                 |
| ps                                            | List of currently running containers                                          |                                                   |
| ps -a                                         | List of all containers, even those exited                                     |                                                   |
| rm container-id                               | remove a container                                                            |                                                   |
| rm container-name                             |                                                                               |                                                   |
| ps -a -q -f status=exited                     | Quiet (-q) list of all containers, filtered (-f) such that status is "exited" |                                                   |
| docker rm $(docker ps -a -q -f status=exited) | Remove all existed containers                                                 |                                                   |
| container prune                               | Remove all stopped containers                                                 |                                                   |
| images                                        |                                                                               |                                                   |
| rmi image-name                                | Remove image                                                                  |                                                   |
| exec container-name command                   | Run a command on an already running container                                 | docker exec  distracted_mcclintock cat /etc/hosts |
| run -d image-name                             | Runs container in the background, so you can use the terminal                 |                                                   |
| attach container-id                           | Brings a running container to the foreground                                  |                                                   |
| stop container-name or id                     | Stops a container from running                                                |                                                   |
| inspect container-id                          | Returns low level details about a container                                   |                                                   |
| history image-name                            | Reveals information about                                                     |                                                   |
`docker run ubuntu sleep 5`

Containers stop when there is no running process within them

## Tags
You can specify the image version you want to pull or run using tags. By default, the `latest` tag is used to pull the latest version
```
docker pull redis:4.0
```


By default, docker doesn't take in input (does not have a standard input). The -i flag makes the image interactable, so it can accept input from the terminal that ran the command
```
docker run -i image-name
```

The `-t` flag connects the application's terminal within the docker image to your terminal. 

In short, ==run console input-output applications using the `docker run -it` command.==

## Port mapping
Every docker container has an IP address assigned by default. Users outside of the container cannot access its IP address or ports. 
To access an internal web application running inside a container, we must map an internal port to a port on the host machine.
```
docker run -p 80:5000 web-app-image
```
Assuming the host machine on which the container is running has an IP address of `192.168.1.1`, then we can access the containerized web app using `http://192.168.1.1:80`
You can run as many instances of the containers as you want and connect them to different ports, as long as the ports are free and not used by other applications.

## Docker containers have their own isolated filesystems
You can connect a directory from the host machine to the container so the data is not lost even if you delete the container

```
docker run -v /some-host-dir:/example-dir/mysql mysql
```


## Set environment variables in docker containers
You can pass in environment variables to a docker container. Say you're running a flask application with some environment variable you want to customize, like the background color of a page.
```
docker run -e APP_COLOR=blue simple-webapp-color-image
```
This instantiates a container with that environment variable. If you run `docker inspect simple-webapp-color-image`, you will see `APP_COLOR=blue` is listed in the configurations

# Creating your Own Docker Image
You might not always find an image for a service you need.

Example of a docker file (ignore the comments)
```
FROM Ubuntu // every image must be built on an OS or another image that is based on an OS

RUN apt-get update // run commands to install dependencies
RUN apt-get install python
RUN pip install flask
RUN pip install flask-mysql

COPY . /opt/source-code  // copy app code from host machine to the image 
ENTRYPOINT FLASK_APP=/apt/source-code/app.py flask run // define the command to run when a user creates and runs a container 
```

To build it and publish it, you can:
```
docker build -t my-username/my-image .
docker push my-username/my-image
```
The `-t` flag sets a tag. And `.` is the directory of the docker build file

When an image is built, Each instruction is a layer built on top of the previous instruction (layer). Each layer only stores the changes from the previous layer. The layers are also cached, so if during building, one layer fails, docker will resume from the previous layer and not start all over again. This makes docker containers fast.

# `CMD` vs `ENTRYPOINT`

Note: commands in docker can be written as a list, where the first element is a command, and the rest are its arguments. So `CMD sleep 5` can be written as `CMD ["sleep", "5"]`

Consider the following image, `ubuntu-sleeper:
```
FROM Ubuntu

CMD ["sleep", "5"]
```
Any commands entered while running the container will override the command `sleep 5`:
```
docker run ubuntu-sleeper sleep 10
```

Now consider the following:
```
FROM Ubuntu
ENTRYPOINT ["sleep"]
```
Any terminal commands will be appended to the `sleep` command:
```
docker run ubuntu-sleeper 10
```
will yield `sleep 10`.

We can combine the ENTRYPOINT and CMD to set defaults

```
FROM Ubuntu
ENTRYPOINT ["sleep"]
CMD ["5"]
```
If the user enters,
```
docker run ubuntu-sleeper
```
without an argument, we get `sleep 5`. But if the user enters 
```
docker run ubuntu-sleeper 10
```
5 gets replaced by 10 and we get `sleep 10`

# Docker Networking
Every container has an IP and MAC address. Docker creates an internal network with a [[Networking#DNS (Domain Name System)|DNS]] for containers to communicate. This internal DNS allows containers to use each other's' names (or IDs) to connect to each other. Recall that DNS converts human readable names to IP addresses.

There are 3 network configurations:
- bridge. This is the default behavior. When you execute `docker run image-name`, Docker creates a network for containers. Each container will have its own IP address that is used internally. We've already seen how to do [[Docker#Port mapping|port mapping]].
- `docker run image-name --network=none`. Containers are completely isolated and do not support networking.
- `docker run image-name --network=host`. Removes the networking isolation between containers and the host. Therefore, containers will directly use the host's ports. No need for port forwarding. But now we can't run multiple instances of the same image using one port. 
Docker automatically creates 1 internal network. But we can customize this using
```
docker network create --driver bridge --subnet 182.18.0.0/16 custom-isolated-networks
```

```
docker network ls
```

Use the `docker inspect container-id` to view the specifics regarding the networking of a container. 

# File system
Docker images are layered and cached. For example, suppose the first 10 instructions of two docker files are identical. When we build the first image, docker creates layers for each instruction, where each layer only builds on top of the previous layer. Now suppose we build the second image. Docker is going to reuse the 10 common layers from the first image, then add the remaining different layers on top. This makes building images very fast.
Now, when you run an image, the inner layers (aka the image layers) are read only and cannot be changed. Docker adds a container layer on top of the image layers. We can also write to this layer. If we need to make changes to a file in the read-only layer, docker will create a temporary copy of that file in the container layer. When the container is destroyed, the container layer is also lost. 
To prevent this, we can create a **volume** on the host machine and mount it on the container. The data from the container layer is therefore stored in the host machine.

For example, the following connects the volume `data_volume` that is located on the host to the dir `/var/lib/mysql` in the container when we run `mysql` image (running an image means creating a container). This is called **volume mounting**.
```
docker volume create data_volume
docker run -v data_volume:/var/lib/mysql mysql
```
On a Linux system, volumes are stored in `/var/lib/docker/volumes`.
If the volume doesn't exist when we execute `docker run`, docker will automatically create it.

You can also bind any directory on the host to a container. We just uses the absolute path instead of volume name. This is called **bind mounting**

The new and preferred command to do mounting is:
```
docker run --mount=bind,source=/data/mydql,target=/var/lib/mysql mysql
```

Docker uses storage drivers to do the layering and mounting. Different host OS will use different storage drivers. Some OSes may support multiple drivers, but docker will automatically use the most efficient.

# Docker Compose
Executing a stack application can be done in two ways
## Individually running and configuring the containers

Image names and ports in the following are probably not accurate
```
docker run -d --name=angular -p 5000:4200 --link express:express angular
docker run -d --name=express express
docker run -d --name=mongodb mongo 
```
Containers names are used for linking (see further down).
Angular is the user interface; it uses port 4200 by default. External users can use port 5000 to access the container. 

We need to use `--link` to make containers aware of each other. In the example above, we entered `--link express:express` for angular. 

In a Linux system of the angular container, this will create an entry in the `/etc/hosts` file like the following
```
172.17.0.2    express
```
The `hosts` file is a plain text file that serves as a local DNS that resolves IP addresses for the containers. So we can write code in the angular container that is able to resolve the name `express` to the IP address of the express container. 

## Using docker compose
Instead of manually starting and configuring each container, we can store the start up configuration in a `docker-compose.yml` file. 

Version 1:
```
express:
	image: express
mongo:
	image: mongo
angular:
	image: angular
	links:
		- express  # shortway of writing express:express
	ports:
		- 5000:4200
```
use `image` for images on the docker hub. use `build` for your custom images that are not necessarily published.
```
image-name:
	build: ./docker-image-file
```

There are 3 main versions of docker compose. 

In version 2, we don't need to use links because a bridged network is automatically created. It also allows you to specify dependencies so that if one container depends an another container, the latter starts first. 
We can also create custom networks and assign the containers to them. This is for controlling traffic flow and added security.
Front end apps communicate with both the back-end and front-end networks.
```
version: 2
services:
	express:
		image: express
		networks:
			- back-end
	mongo:
		image: mongo
		depends_on:
			- express
		networks:
			- back-end
	angular:
		image: angular
		ports:
			- 5000:4200
		depends_on:
			- express
		networks:
			- front-end
			- back-end
networks:
	front-end:
	back-end:
```

Version 3 offers support for docker swarm 

can be used when containers (components) are on a single host

# Docker Registry

A docker registry like `docker.io` is a cloud service that stores images. It's like GitHub.
```
image: registry/username/image-name
image: docker.io/nginx/nginx
```
If you don't specify a registry, docker assumes it's `docker.io`. Similarly, if you don't specify an account name, docker will assume it's the same as the image name.

`gcr.io` for google registry. These are public.

You can push or pull into a private registry by first logging in.
```
docker login private-registry.io
```

You can manage your images on a private, local network by the registry service, which itself is an image.
```
docker run -d -p 5000:5000 --name registry registry:2
```

To push an image
1. First build the image
```
docker image tag my-image localhost:5000/my-image
```
if you are on using the registry hosting computer.
2. Then push
```
docker push localhost:5000/my-image
```

If you are on another computer on the network, then use the IP address of the computer that's hosing the registry
```
docker push 192.178.56.100:5000/my-image
```

# Docker Engine
The docker engine is the host and the docker program installed on it. The architecture of docker is made of 3 parts. 
1. The Daemon 
2. REST API
3. CLI
The CLI uses the API to communicate with the Daemon, which is the kernel and manages processes, images, containers, volumes, etc.
The CLI can connect to an engine on a remote computer.
```
docker -H=remote-docker-engine-ip:2375 run nginx
```

Docker containers are isolated because each use their own namespace. In reality, they all share resources with the underlying host computer. 
For example, a process in a container will also appear in the list of processes on the host computer. That process has multiple ids. This way, the container will think it has its own process. It thinks it's independent from the host.

We can control the resources a container can use. 
```
docker run --cups=.5 --memory=100m ubuntu
```
This means the container will use no more than 50% of processing power, and no more than 100 megabytes of RAM memory.


# Docker Orchestration
Solutions to manage containers. Tools and scripts to automatically deploy an additional instance of a container when the load is high, or when replace a container when it fails, or when the host fails. It also manages advanced networking between containers, even across different hosts.
In short, it manages scaling your application. Examples of solutions are docker swarm, Kubernetes, and MESOS.

## Docker Swarm (by Docker)
Multiple hosts form a cluster
Master and slave relationship between hosts 

## Kubernetes (by Google)

## MESOS (by Apache)




# Other Notes
	In the case of malware, the compromised container can’t be terminated and replaced with a new clean image.
[source](https://www.liquidweb.com/blog/virtualization-vs-containerization/)
Why not?
