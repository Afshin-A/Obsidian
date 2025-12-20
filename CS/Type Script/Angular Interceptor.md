An interceptor in Angular is a service that automatically *intercepts* and modifies http requests.
For example, we don't want to have to manually add JWT to every http request. So we use an interceptor service.
When an http request is initiated, it goes through multiple interceptors until the last one fires it off to its destination. It works like a pipeline. 