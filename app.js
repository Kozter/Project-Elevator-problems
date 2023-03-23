const express = require('express');
const bodyParser = require('body-parser');
const { MongoClient } = require('mongodb');

const app = express();
const port = 4000;

const uri = 'mongodb://127.0.0.1:27017/Elevator-accelerometer-monitor';
const client = new MongoClient(uri, { useUnifiedTopology: true });

app.use(bodyParser.urlencoded({ extended: false }));

app.post('/elevator-data', async (req, res) => {
  try {
    const elevatorId = req.body.elevator_id;
    const x = parseFloat(req.body.x);
    const y = parseFloat(req.body.y);
    const z = parseFloat(req.body.z);

    await client.connect();

    const database = client.db('Elevator-accelerometer-monitor');
    const collection = database.collection('data');

    const doc = {
      timestamp: new Date(),
      elevatorId,
      acceleration: {
        x,
        y,
        z,
      },
    };

    const result = await collection.insertOne(doc);
    console.log(`New document inserted with _id: ${result.insertedId}`);

    const X_THRESHOLD = 2.0;
    const Y_THRESHOLD = 2.0;
    const Z_THRESHOLD = 2.0;

    if (Math.abs(x) > X_THRESHOLD || Math.abs(y) > Y_THRESHOLD || Math.abs(z) > Z_THRESHOLD) {
      console.log("Alert: Unusual movement detected");
      console.log(`Elevator ID: ${elevatorId}, X: ${x}, Y: ${y}, Z: ${z}`);
    }

    res.status(200).send('Data saved');
  } catch (error) {
    console.error(error);
    res.status(500).send('Error saving data');
  } finally {
    await client.close();
  }
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
