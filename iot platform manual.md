# Internet of Things platform setup

### Create an IBMid on the IBM CLOUD
In order to work in the IBM Cloud (formerly known as Bluemix) you need to register and get an IBMid. 
If you already have an IBMid, just log in to the IBM Cloud. 
Else, follow next steps to create one. 
1. Go to https://cloud.ibm.com/login
2. Click Create an IBM Cloud account
3. Follow the steps to create you IBMid 
You now can use the IBM Cloud. Lots of the available services has a free tier, so you can now start experimenting for free

### Deploy IoT platform starter service
The IoT Platform Starterservice helps you deploy SDK for Node.js as your Application, with Watson IoT Platform service and the Cloudant NoSQL DB service binded to your IoT Application. Here, the Device and Gateway specific IoT events shall be managed and handled on the IoT Platform, while the Cloudant NoSQL DB actsas the default DB for your IoT requirements. Node-RED shall be the default User Interface and is considered one of the fastest means to begin your IoT Application development
Following set of steps details out on the deployment of the IoT Platform Starterservice: 
1. Log into IBM Cloud (https://cloud.ibm.com/login) with your IBMid and access the Catalog. 
2. Choose to click on the Internet of Things Platform Starterservice. This can be found in the 'Starter Kits' section of the catalog.
3. Provide auniqueApp Name (e.g. My-initials-Workshop), which shall be the Host name for your application, and keep the default values for Domain, Location, Organization and Space.
4. Keep the default plans for SDK for Node.js, Cloudant NoSQL DB and IoT Platform. 
5. Click on Create, provided on the bottom-right corner of the screen, to go ahead and deploy the Starter service 
6. The deployment process takes couple of minutes to complete. 
7. Click the Hamburger-menu on the top left corner and select Resource list. 
8. You should see your application with an Up & Running status (Green dot) along the IoT Platform Service and the Cloudant database. Note: if the application is not Starting or Running, start it manually using the three-dots-menu on the right. 
9. Click on the application name to open the information page on IBM Cloud. Examine the menus on the left. 
10. On the Overview page click on Visit App URL to browse to the Node-RED flow editor that you use to create your application. 
