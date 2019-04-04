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

# IBM Watson and devices
### IBM Watson
We will now create some virtual devices in the IBM Watson application. These devices will represent the Arduinos we use in our pool device. The physical arduino will send messages to the virtual devices on Watson, the devices on watson will then send them to the Node-Red platorm (more info about this later)

Follow these steps to launch the Watson platform:
1. Go to the IBM Cloud dashboard if you aren't here already.
2. Within the Dashboard find the findthe Internet of Things Platform service listed under “Cloud Foundry Services”. The name will be different from the one in this screenshot. Click on it to open the main page
3. Observe the Welcome page click on Launchbutton to enter into the IBM Watson IoT Platform organization space.
4. Observe the right top corner of the page, where you’ll find the six character Organization ID that is created for you to identify your instance of the Watson IoT Platform service. Here you can add, connect and manage your IoT devices. __write this id down somewhere__

### Creating devices
Create Device Type Each device connected to the IBM Watson IoTPlatform is associated with a device type. Device types are intended to be groups of devices which share common characteristics. So in order to add devices in IBM Watson IoT Platform, one need to create a device type.Following are the instructions for creating a Device Type:
1. In the IBM Watson IoT Platform dashboard, click DEVICES menu. 
2. Select theDevice Types tab, then click on the Add Device Type button. 
3. Observe that there are two options provided now, namely Device type and Gateway type. Select 'Device type'.
4. For the device type, enter __ESP32__. Optionally add a description, then click Next.
5. Observe that a template page is given where you can select and define one or more attributes. All of these attributes are optional. They will be used as a template for new devices that are assigned this device type. Attributes that you do not define may still be edited individually later when you add the device. Define any attributes if you want, then click Done.

We have successfully create a device type in IBM Watson.
Now we need to create a device that matches the device type.
Follow these steps:
1. In the IBM Watson IoT Platform dashboard choose the Devices menu on the left, click the Browse tab and then Add Device button.
2. Choose the device type "ESP32" that we created in the last step. For device id enter "arduino", then click Next.
3. In the Device Information page you can enter more information about your device. Click Next.
4. In the next page, you can either add your own authentication token, or allow the IBM Watson IoT Platform to generate a token for you. The IBM Watson IoT Platform generated token will be 18 characters long and will contain a mix of alphanumeric characters and symbols. The token will be returned to you at the end of the registration process. In case if you want to add your own token, enter the token, then click Next.
5. you will be given a summary page to verify the details before adding the device to IBM Watson IoT Platform. Verify and click Done.
6. This last page will show all the device information. __Write all this data down somewhere, Especially the token!__

We have now successfuly created a registered device!
(When configuring the mqqt connection on the arduino you will need the token. )

# Cloudant database

We will use the cloudant database to store all the data our arduino measures.
Cloudant is a CouchDb database that doesnt use SQL to store data, but uses search indexes and a different query language to retrieve data.
Don't worry, you do not need to know anything about this, we will just setup the database. The importing and exporing of the data is done automatically by our node-red flow.

### Creating the Cloudant database

Follow these steps to setup the cloudant DB:
1. Browse back to the IBM cloud dashboard. (hamburger-menu on the top left corner and select Dashboard).
2. On the dashboard, click on  'Cloud foundry services'.
3. Under 'Services' There should be a cloudand-pz listed, click on it.
4. On the next page, click on 'Launch cloudant dashboard'.
5. When you reached the dashboard, click on 'Create database' in the top right corner. Name this database 'phmetingen'.
6. When the database appears in the list of databases, click on the one we just created.
7. Next, create a new search index in this database.

![alt text](https://github.com/emildekeyser/projectweek-arduino-water/blob/master/img/node-red6.png "Create search index")

8. Copy the following settings for the search index:

![alt text](https://github.com/emildekeyser/projectweek-arduino-water/blob/master/img/node-red7.png "Create search index")

```
function (doc) {
   if (doc.timestamp) {
     index("searchTime", doc.timestamp, {"store": true, "facet":true}); 
    }
}
```

The database is now ready to be used!


# Using node red with the IBM device

We are almost finished, all that is left is creating a node-red flow that will use our arduino to create a nice dashboard and save data in a database.

### Node Red flow

Follow these steps to import the node-red flow we have made for you:
1. Browse back to the IBM cloud dashboard. (hamburger-menu on the top left corner and select Dashboard).
2. Click on the application name to open the information page on IBM Cloud. Examine the menus on the left.
3. On the Overview page click on VisitApp URLto browse to the Node-RED flow editor that you use to create your application.  
4. As the Application launches, it prompts you to complete couple of steps: Secure the Node-RED Editorand optionally, allows you to Browse available nodes.
  Click on Next to continue.
  To secure your Node-RED Editor and the flows associated with it, configure the credentials with a custom User ID and Password of your choice. Optionally, choose to grant access public in Read-Only mode or grant Write permission to all.
  Click on Next to continue.
5. The last step in the configuration process summarizes your selections & choices. Click on Finishto complete the Application configuration.
6. The Configuration choices made shall take couple of moments to be applied to your current Application environment.
7. Post applying your Configuration settings, you are now good to start with your Node-RED editor. Click on the Go to your Node-RED flow editor to launch the editor.

Before you can import the flow we made in the editor you will need to import a 'node palette'.

Go to 'manage palette' as shown here:
![alt text](https://github.com/emildekeyser/projectweek-arduino-water/blob/master/img/node-red2.png "manage palette")

Then search for the dashboard plugin and install it:
![alt text](https://github.com/emildekeyser/projectweek-arduino-water/blob/master/img/node-red3.png "Importing our flow")

Here is a list of all node palettes that should be installed: 
(Make sure these are installed or the flow will not work correctly)

| Palettes      |
| ------------- |
| node-red      | 
| node-red-bluemix-nodes      | 
| node-red-contrib-bluemix-hdfs |
| node-red-contrib-email-out |
| node-red-contrib-ibm-wiotp-device-ops |
| node-red-contrib-ibmpush |
| node-red-contrib-iot-virtual-device |
| node-red-contrib-scx-ibmiotapp |
| node-red-dashboard |
| node-red-node-cf-cloudant |
| node-red-node-watson |  

When this is finished you can import our flow.

In the node red editor it is very simple to import our flow.  
![alt text](https://github.com/emildekeyser/projectweek-arduino-water/blob/master/img/node-red.png "Importing our flow")

In the window that pops up, copy and paste the following json text:
```
{
	"json": "TODO";
}
```

The flow is now imported. On the top-right of the page 'click' deploy. Node red is now running!

If you want you can play around with some of the nodes to see what they do.
For more info on node-red and what all the different nodes and flows do/mean, you can visit their site [here](https://nodered.org)


### Final product

The Internet side of our IoT project is now finished.
If you have also configured the arduino and it is running, you are done!

To view the dashboard that node-red generated, go here:

![alt text](https://github.com/emildekeyser/projectweek-arduino-water/blob/master/img/node-red4.png "Viewing the dashboard")

If you cannot find this link make sure the node-red-dashboard plugin is installed and that you have deployed the node-red flow.

The result should be this:
![alt text](https://github.com/emildekeyser/projectweek-arduino-water/blob/master/img/node-red5.png "Dashboard result")

Everything displayed here comes directly from the arduino.
