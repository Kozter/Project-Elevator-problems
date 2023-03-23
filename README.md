# Project: Elevator problems
Objective: “While at a party, you meet an old friend from school. She is now in the elevator business and has a problem with a specific elevator that is hard to solve. Their customer complains since at an elevator is making more noise than it should. This is annoying to the office users. The problem is that the noise never happens when they wait for it to happen - so they need a solution that can register any unusual movement of the elevator so they can analyze it. It is also nice if the solution can alert them if extensive shaking happens.”
- Device: Adafruit Feather ESP32 board 
- Sensors: Adafruit LIS3DH accelerometer

# Project:
The project involves setting up an IoT device that monitors the movement of an elevator using an accelerometer that sends the monitoring data to a server. The device is built using an Adafruit Feather ESP32 board and an Adafruit LIS3DH accelerometer sensor.
The device connects to a Wi-Fi network and sends data to a server using HTTP POST requests. The server is built using Node.js and MongoDB, and it receives the accelerometer data and stores it in a database.

### Accelerometer
Additionally, the project includes implementing an alert system that detects unusual movement of the elevator. This is achieved by setting up thresholds for an accelerometer which is read every 500 milliseconds and triggers an alert if it should go beyond the set thresholds.
The x, y, and z values of the accelerometer gives the acceleration experienced in each of the three dimensions of the sensor's frame of reference and are used to indicate unusual movement in the elevator. The code sends a POST request to the server with the accelerometer readings and elevator ID and logs a message in the console ("Alert: Unusual
movement detected"), and can also be handled by sending an email, SMS notification, or any other method preferred.

### HTTP requests - Express
The server is built using Express, a popular web framework for Node.js. Express provides a simple way to handle HTTP requests and define the routes and middleware for our application. We have used Express to define a route /elevator-data that accepts POST requests from the Arduino board and logs the received data to the console.

### MongoDB - NoSQL
To store the data received from the Arduino board, we have used MongoDB, a NoSQL document database. MongoDB stores data in JSON-like documents, making it easy to work
with data in JavaScript-based applications. We have used the MongoDB driver for Node.js to connect to the database and perform create, read, update, delete operations on the data.

### Mongoose
We have also used Mongoose, a library for MongoDB, to define the schema for our data and provide a higher level of abstraction when interacting with the database. Mongoose allows us to define a schema for our data and provides a set of methods for querying and manipulating the data.

### MongoDB Compass
MongoDB Compass is a graphical user interface for MongoDB that allows us to easily view and manipulate data in the database. We have used MongoDB Compass to view the data received from the Arduino board and verify that it is being stored correctly in the database.

### Extending product
We could extend this solution from up to 100 elevators as we have a good starting point:

Unique ID:
- We should have unique IDs on each device installed based on the address of the Wi-Fi module or have a unique predefined string included that is sent to the server.

Dashboard:
- A dashboard that can support multiple elevator monitoring.
- The dashboard should include user filter options and make it possible for data analysis.
- Data visualization, elevator performance comparison, and remote configuration of monitoring settings for each elevator are features that could be considered.

Notification system:
- Modify the notification system (e.g., email, SMS) to include the elevator ID in the alerts, allowing maintenance teams to identify which elevator is experiencing issues quickly.

Database scalability:
- The database should handle data from multiple elevators.
- The data should be organized based on the different elevator IDs and timestamps to enable efficient data retrieval and analysis.
