I have uploaded the Trained AI model. 

You have to upload the trained AI models into esp 32 cam (Specific Cam model :- ESP_32_AI_THINKER)

Now you have to make a code for,

The trained model will run inside the ESP 32 cam so, 

there should be 5 seconds gap to check for the visuals it should iterate for both cams.  

ESP 32 cam should the instruction signals to Arduino to control the traffic lights.

Traffic lights controls are coded to the Arduino it should change anything else, just only change the timer for the traffic system.

Only responce sent by the esp 32 cam to Arduino is the timer it should apply. 

Low traffic = 5 seconds
High traffic = 10 seconds

the labels of trained AI model is in this form,

for low traffic :- low_traffic
for high traffic :-  medium_traffic

the esp 32 should sent serial communication to Arduino using the TX, RX ports
Esp 32 RX, TX ports
Arduino softserial ports.