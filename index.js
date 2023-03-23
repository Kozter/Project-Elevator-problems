const mongoose = require("mongoose");

const elevatorDataSchema = new mongoose.Schema({
  x: { type: Number, required: true },
  y: { type: Number, required: true },
  z: { type: Number, required: true },
  timestamp: { type: Date, default: Date.now }
});

elevatorDataSchema.methods.saveData = async function() {
  try {
    await this.save();
    console.log("Data saved to MongoDB");
  } catch (error) {
    console.error("Error saving data to MongoDB", error);
  }
};

const ElevatorData = mongoose.model("ElevatorData", elevatorDataSchema);

module.exports = ElevatorData;