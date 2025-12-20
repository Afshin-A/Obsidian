We deploy our Docker container, Google takes care of the rest

First, activate your virtual environment
Generate `requirements.txt`
```
pip freeze > requirements.txt
```

# Upload Container to Google Container Registry (GCR)



Email domains are separate than website domains

If using VS Code and the environment variables in a flask application, retrieved via `os.getenviron["VAR_NAME"]` are not updated after making a change, restart VS Code. 

docker run -p 8080:8080 --env-file .env flask-app
```
gcloud auth login
```
this opens your browser to log in, after which we can access our project

with simple caching for flask caching, all pages including the users page are being drawn  from browser cache. this means that i have to restart the application before changes in the database are shown in the users page. 
with the null caching option, the page we click on is being requested from the server again (http code 200) while all other pages are being drawn from the cache with http code 304

it's important the application runs on port 8080 because that is the port that google cloud run requires for the application to be available to public

```
gcloud config set project world-of-healthcare
```



```
docker tag flask-app us-south1-docker.pkg.dev/[PROJECT_ID]/[REPOSITORY_NAME]/flask-app


docker tag flask-app us-south1-docker.pkg.dev/world-of-healthcare/flask-app-image/flask-app

docker push us-south1-docker.pkg.dev/world-of-healthcare/flask-app-image/flask-app

gcloud run deploy flask-app --image=us-south1-docker.pkg.dev/world-of-healthcare/flask-app-image --platform=managed --region=us-south1 --allow-unauthenticated


gcloud run deploy flask-app --image=flask-app us-south1-docker.pkg.dev/world-of-healthcare/flask-app-image --platform=managed --region=us-south1 --allow-unauthenticated

gcloud projects get-iam-policy world-of-healthcare


```



```
gcloud run domain-mappings create --service flask-app --domain worldofhealthcaretx.com --region us-south1
```


ctrl + shift + e
ctrl + b

win + ctrl + t


	Lazy loading is **a technique for waiting to load certain parts of a webpage — especially images — until they are needed**. Instead of loading everything all at once, known as "eager" loading, the browser does not request certain resources until the user interacts in such a way that the resources are needed. 
[CloudFlare](https://www.cloudflare.com/learning/performance/what-is-lazy-loading/)