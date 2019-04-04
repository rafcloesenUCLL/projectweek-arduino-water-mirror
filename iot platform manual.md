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
[{"id":"516447f9.c10168","type":"tab","label":"merged","disabled":false,"info":""},{"id":"86ee9776.f9276","type":"ibmiot in","z":"516447f9.c10168","authentication":"boundService","apiKey":"","inputType":"evt","logicalInterface":"","ruleId":"","deviceId":"arduino","applicationId":"","deviceType":"ESP32","eventType":"status","commandType":"","format":"json","name":"IBM IoT","service":"registered","allDevices":false,"allApplications":"","allDeviceTypes":"","allLogicalInterfaces":"","allEvents":false,"allCommands":"","allFormats":"","qos":0,"x":50,"y":300,"wires":[["fbd0f47d.558ed","fa760766.4be19","573a7b04.e25444","f7df8294.d68e48","ecfa4270.13e008"]]},{"id":"6033ce6a.a77638","type":"cloudant out","z":"516447f9.c10168","name":"","cloudant":"","database":"phmetingen","service":"ucll-team1-cloudantNoSQLDB","payonly":true,"operation":"insert","x":870,"y":100,"wires":[]},{"id":"20bdc76f.4f0ec8","type":"change","z":"516447f9.c10168","name":"","rules":[{"t":"set","p":"payload","pt":"msg","to":"payload.d","tot":"msg"},{"t":"set","p":"payload.timestamp","pt":"msg","to":"","tot":"date"}],"action":"","property":"","from":"","to":"","reg":false,"x":580,"y":100,"wires":[["6033ce6a.a77638"]]},{"id":"87557a48.411d78","type":"comment","z":"516447f9.c10168","name":"insert measurement into database","info":"","x":340,"y":60,"wires":[]},{"id":"fbd0f47d.558ed","type":"switch","z":"516447f9.c10168","name":"","property":"payload.d.ph","propertyType":"msg","rules":[{"t":"btwn","v":"0","vt":"num","v2":"2.5","v2t":"num"},{"t":"btwn","v":"0","vt":"num","v2":"5","v2t":"num"},{"t":"btwn","v":"5","vt":"num","v2":"9","v2t":"num"},{"t":"gte","v":"9","vt":"num"}],"checkall":"true","repair":false,"outputs":4,"x":250,"y":300,"wires":[["3fb3c679.5b9d5a"],["b3eddcbb.a9a8c8"],["43e36df.fb8fc14"],["48dc964a.2cb238"]]},{"id":"43e36df.fb8fc14","type":"change","z":"516447f9.c10168","name":"pH is normal","rules":[{"t":"set","p":"payload.d.message","pt":"msg","to":"pH is normal","tot":"str"}],"action":"","property":"","from":"","to":"","reg":false,"x":570,"y":360,"wires":[["c341b79f.661bc"]]},{"id":"48dc964a.2cb238","type":"change","z":"516447f9.c10168","name":"pH is too high","rules":[{"t":"set","p":"payload.d","pt":"msg","to":"{\"valve\":2,\"message\":\"pH is too high!\"}","tot":"json"}],"action":"","property":"","from":"","to":"","reg":false,"x":580,"y":400,"wires":[["c341b79f.661bc"]]},{"id":"b3eddcbb.a9a8c8","type":"change","z":"516447f9.c10168","name":"pH is too low","rules":[{"t":"set","p":"payload.d","pt":"msg","to":"{\"valve\":1,\"message\":\"pH is too low!\"}","tot":"json"}],"action":"","property":"","from":"","to":"","reg":false,"x":580,"y":320,"wires":[["966f1cc0.cafd1","c341b79f.661bc"]]},{"id":"3fb3c679.5b9d5a","type":"change","z":"516447f9.c10168","name":"make mail","rules":[{"t":"set","p":"topic","pt":"msg","to":"Dangerous pH measured!","tot":"str"},{"t":"set","p":"payload","pt":"msg","to":"payload.d.ph","tot":"msg"},{"t":"set","p":"html","pt":"msg","to":"'Hello!<br><br> The pH measuring device in your pool has measured a pH level of ' & payload & '. Any pH value below 2.5 is considered dangerous, do not go swimming until the pH is at a higher level again. <br><br>You can check the pH level realtime on your dashboard:<br> <a href=\"https://ucll-team1.eu-gb.mybluemix.net/ui/\">https://ucll-team1.eu-gb.mybluemix.net/ui/</a>'","tot":"jsonata"}],"action":"","property":"","from":"","to":"","reg":false,"x":570,"y":280,"wires":[["eec6b5db.6ee74"]]},{"id":"c938b53f.8008f","type":"e-mail out","z":"516447f9.c10168","server":"smtp.gmail.com","port":"465","secure":true,"name":"PoolPhEmail@gmail.com","dname":"send email when ph dangerous","x":1070,"y":280,"wires":[[]]},{"id":"eec6b5db.6ee74","type":"delay","z":"516447f9.c10168","name":"","pauseType":"rate","timeout":"5","timeoutUnits":"seconds","rate":"1","nbRateUnits":"30","rateUnits":"minute","randomFirst":"1","randomLast":"5","randomUnits":"seconds","drop":true,"x":810,"y":280,"wires":[["c938b53f.8008f"]]},{"id":"fa760766.4be19","type":"switch","z":"516447f9.c10168","name":"","property":"payload.d.product1","propertyType":"msg","rules":[{"t":"gt","v":"0.80","vt":"num"},{"t":"gt","v":"0","vt":"str"}],"checkall":"true","repair":false,"outputs":2,"x":250,"y":240,"wires":[["3d9b1d43.9ce87a"],["3687619f.77883e"]]},{"id":"3d9b1d43.9ce87a","type":"change","z":"516447f9.c10168","name":"make mail","rules":[{"t":"set","p":"topic","pt":"msg","to":"low product","tot":"str"},{"t":"set","p":"payload","pt":"msg","to":"100 * (1 - payload.d.product1)","tot":"jsonata"},{"t":"set","p":"html","pt":"msg","to":"'Hello!<br><br> This is an email to notify you that you only have ' & payload & '% of your product left! When this product runs out the machine will no longer be able to increase the pH. <br><br>Please try to refill the product storage as soon as possible.'","tot":"jsonata"}],"action":"","property":"","from":"","to":"","reg":false,"x":570,"y":240,"wires":[["dd63deaf.b1d698"]]},{"id":"dd63deaf.b1d698","type":"delay","z":"516447f9.c10168","name":"","pauseType":"rate","timeout":"5","timeoutUnits":"seconds","rate":"1","nbRateUnits":"30","rateUnits":"minute","randomFirst":"1","randomLast":"5","randomUnits":"seconds","drop":true,"x":810,"y":240,"wires":[["faed86f6.cf1468"]]},{"id":"faed86f6.cf1468","type":"e-mail out","z":"516447f9.c10168","server":"smtp.gmail.com","port":"465","secure":true,"name":"PoolPhEmail@gmail.com","dname":"send email when product low","x":1070,"y":240,"wires":[[]]},{"id":"7279f6c5.d77098","type":"comment","z":"516447f9.c10168","name":"check arduino values","info":"","x":300,"y":200,"wires":[]},{"id":"fa3757ce.29091","type":"cloudant in","z":"516447f9.c10168","name":"","cloudant":"","database":"phmetingen","service":"ucll-team1-cloudantNoSQLDB","search":"_idx_","design":"searchTime","index":"searchTime","x":690,"y":520,"wires":[["57a69fba.33966"]]},{"id":"573a7b04.e25444","type":"delay","z":"516447f9.c10168","name":"Wait for db insert","pauseType":"delay","timeout":"50","timeoutUnits":"milliseconds","rate":"1","nbRateUnits":"1","rateUnits":"second","randomFirst":"1","randomLast":"5","randomUnits":"seconds","drop":false,"x":290,"y":520,"wires":[["281b8d6a.74566a"]]},{"id":"bfcbf745.16e328","type":"ui_button","z":"516447f9.c10168","name":"Refresh","group":"12da06cb.54aa31","order":2,"width":0,"height":0,"passthru":false,"label":"Refresh","tooltip":"Refresh the log","color":"","bgcolor":"","icon":"","payload":"true","payloadType":"bool","topic":"","x":260,"y":600,"wires":[["281b8d6a.74566a"]]},{"id":"ac8f17c8.628e8","type":"ui_template","z":"516447f9.c10168","group":"12da06cb.54aa31","name":"Log","order":1,"width":"10","height":"12","format":"<div>\n\t<div style=\"display: flex !important; flex-direction: row !important; width: 100% !important;justify-content: space-around !important; border-bottom: 1px solid #a92525 !important; padding-bottom: 5px !important\">\n\t\t<div>pH</div>\n\t\t<div>Time</div>\n\t\t<div>IP-adress</div>\n\t</div> \n\t<div ng-repeat=\"meting in msg.payload\" style=\"display: flex !important; flex-direction: row !important; width: 100% !important;justify-content: space-around !important; margin-top: 10px !important\">\n\t\t<div>{{meting.ph}}</div>\n\t\t<div>{{meting.timestamp | date:\"medium\"}}</div>\n\t\t<div>{{meting.ip}}</div>\n\t</div>\n</div>","storeOutMessages":true,"fwdInMessages":true,"templateScope":"local","x":990,"y":520,"wires":[[]]},{"id":"b7c1a993.b442a8","type":"comment","z":"516447f9.c10168","name":"fetch measurements from database","info":"","x":340,"y":480,"wires":[]},{"id":"de06b59c.e82a48","type":"inject","z":"516447f9.c10168","name":"fire on start","topic":"","payload":"","payloadType":"date","repeat":"","crontab":"","once":true,"onceDelay":0.1,"x":270,"y":560,"wires":[["281b8d6a.74566a"]]},{"id":"966f1cc0.cafd1","type":"ibmiot out","z":"516447f9.c10168","authentication":"boundService","apiKey":"","outputType":"cmd","deviceId":"arduino","deviceType":"ESP32","eventCommandType":"phmessage","format":"json","data":"valve","qos":0,"name":"IBM IoT","service":"registered","x":780,"y":320,"wires":[]},{"id":"c341b79f.661bc","type":"ui_text","z":"516447f9.c10168","group":"85773742.e732e8","order":3,"width":"10","height":"1","name":"","label":"measured pH","format":"{{msg.payload.d.message}}","layout":"col-center","x":800,"y":400,"wires":[]},{"id":"63d95cf7.84d54c","type":"comment","z":"516447f9.c10168","name":"other html elements","info":"","x":290,"y":700,"wires":[]},{"id":"f7df8294.d68e48","type":"ui_gauge","z":"516447f9.c10168","name":"","group":"85773742.e732e8","order":1,"width":"10","height":"6","gtype":"gage","title":"gauge","label":"units","format":"{{msg.payload.d.ph}}","min":0,"max":"14","colors":["#800000","#00ff00","#800000"],"seg1":"4.99","seg2":"8.99","x":250,"y":740,"wires":[]},{"id":"281b8d6a.74566a","type":"change","z":"516447f9.c10168","name":"Query","rules":[{"t":"delete","p":"payload","pt":"msg"},{"t":"set","p":"payload.q","pt":"msg","to":"*:*","tot":"str"},{"t":"set","p":"payload.sort","pt":"msg","to":"-searchTime","tot":"str"},{"t":"set","p":"payload.limit","pt":"msg","to":"22","tot":"num"}],"action":"","property":"","from":"","to":"","reg":false,"x":550,"y":520,"wires":[["fa3757ce.29091"]]},{"id":"b50fb9a7.543a78","type":"ui_chart","z":"516447f9.c10168","name":"","group":"85773742.e732e8","order":0,"width":"10","height":"6","label":"chart","chartType":"line","legend":"false","xformat":"HH:mm:ss","interpolate":"linear","nodata":"no data","dot":true,"ymin":"0","ymax":"14","removeOlder":"0","removeOlderPoints":"5","removeOlderUnit":"3600","cutout":0,"useOneColor":false,"colors":["#1f77b4","#aec7e8","#ff7f0e","#2ca02c","#98df8a","#d62728","#ff9896","#9467bd","#c5b0d5"],"useOldStyle":false,"outputs":1,"x":1150,"y":560,"wires":[[]]},{"id":"29d80064.000e98","type":"function","z":"516447f9.c10168","name":"format","func":"let result =  [];\n\nfor (let i = 0; i < msg.payload.length; i++) {\n    result.push({\"x\": msg.payload[i].timestamp, \"y\": msg.payload[i].ph})\n}\n\nmsg.payload = [{\n\"series\": [\"pH\"],\n\"data\": [\n     result\n],\n\"labels\": [\"\"]\n}];\n\nreturn msg;","outputs":1,"noerr":0,"x":990,"y":560,"wires":[["b50fb9a7.543a78"]]},{"id":"3d117482.de0f9c","type":"ui_gauge","z":"516447f9.c10168","name":"display % product","group":"19052108.7b3837","order":1,"width":"10","height":"8","gtype":"wave","title":"","label":"% left","format":"{{value}}","min":0,"max":"100","colors":["#00b500","#e6e600","#ca3838"],"seg1":"","seg2":"","x":810,"y":200,"wires":[]},{"id":"3687619f.77883e","type":"change","z":"516447f9.c10168","name":"get product","rules":[{"t":"set","p":"payload","pt":"msg","to":"payload.d.product1","tot":"msg"},{"t":"set","p":"payload","pt":"msg","to":"(1 - payload) * 100","tot":"jsonata"}],"action":"","property":"","from":"","to":"","reg":false,"x":570,"y":200,"wires":[["3d117482.de0f9c","fc69dc64.faffe"]]},{"id":"ecfa4270.13e008","type":"switch","z":"516447f9.c10168","name":"","property":"payload.d.ph","propertyType":"msg","rules":[{"t":"gt","v":"0","vt":"num"}],"checkall":"true","repair":false,"outputs":1,"x":250,"y":100,"wires":[["20bdc76f.4f0ec8"]]},{"id":"57a69fba.33966","type":"switch","z":"516447f9.c10168","name":"nullcheck","property":"payload","propertyType":"msg","rules":[{"t":"nempty"}],"checkall":"true","repair":false,"outputs":1,"x":840,"y":520,"wires":[["ac8f17c8.628e8","29d80064.000e98"]]},{"id":"fc69dc64.faffe","type":"ui_text","z":"516447f9.c10168","group":"19052108.7b3837","order":2,"width":"10","height":"3","name":"","label":"Information","format":"You currently have {{msg.payload}}% left of product. <br>This product is used to increase the pH of the water when the pH drops below 5. <br><br>When your remaining products drops below 20% you will be sent an email.","layout":"col-center","x":790,"y":160,"wires":[]},{"id":"12da06cb.54aa31","type":"ui_group","z":"","name":"Measurement history","tab":"5c4a8d06.243274","order":2,"disp":true,"width":"10","collapse":false},{"id":"85773742.e732e8","type":"ui_group","z":"","name":"Gauge","tab":"5c4a8d06.243274","order":1,"disp":true,"width":"10","collapse":false},{"id":"19052108.7b3837","type":"ui_group","z":"","name":"Amount","tab":"5940bfa3.91c89","order":1,"disp":true,"width":"10","collapse":false},{"id":"5c4a8d06.243274","type":"ui_tab","z":"","name":"pH","icon":"dashboard","order":3,"disabled":false,"hidden":false},{"id":"5940bfa3.91c89","type":"ui_tab","z":"","name":"Product","icon":"dashboard","order":3,"disabled":false,"hidden":false}]
```

Before we can deploy the flow, you need to configure the email nodes.

Double click on them to configure them, a window should pop-up:

![alt text](https://github.com/emildekeyser/projectweek-arduino-water/blob/master/img/node-red8.png "Configure email nodes")

Fill in the node as follows:

We suggest you create a fake email adress to use for this project. Creating a gmail account takes less than 5 minutes and is very easy.
You can have node-red send the emails to your actual email adress, however you probably dont want to give node-red access to log in to your email.

![alt text](https://github.com/emildekeyser/projectweek-arduino-water/blob/master/img/node-red9.png "Configure email nodes")


__Make sure you configured both the email nodes__
When everything is ready, you can deploy the flow by clicking 'deploy' in the top right corner. Node red is now running!

If you want you can play around with some of the nodes to see what they do.
For more info on node-red and what all the different nodes and flows do/mean, you can visit their site [here](https://nodered.org)


### Final product

The Internet side of our IoT project is now finished.
If you have also configured the arduino and it is running, you are done!

To view the dashboard that node-red generated, go here:

![alt text](https://github.com/emildekeyser/projectweek-arduino-water/blob/master/img/node-red4.png "Viewing the dashboard")

If you cannot find this link make sure the node-red-dashboard plugin is installed and that you have deployed the node-red flow.

The result should look something this:
![alt text](https://github.com/emildekeyser/projectweek-arduino-water/blob/master/img/node-red5.png "Dashboard result")

Everything displayed here comes directly from the arduino.
