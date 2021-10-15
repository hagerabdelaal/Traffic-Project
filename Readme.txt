Ain Shams University - Faculty of Engineering
CSE316 Microcontrollers and Interfacing
Fall 2020

Team Members
Shady Adel Ezzat Fahmy - 19P5956
Youmna Mohamed Mahmoud Ali - 18P7241
Dahlia Tarek AbdelFattah Ahmad Ghonim - 19P2114


Traffic Light Controller
The system consists of two car traffic lights and two pedestrain traffic lights; one pedestrain traffic light with each car traffic light.
One car traffic light allows cars to move from north to south, and the other allows cars to move from east to west. The car traffic light is 
green, yellow, or red, and the pedestrian traffic light is either green or red, and it has a button.
So we have:
- car traffic light 1 (nourth-south): green, yellow, red
- car traffic light 2 (east-west): green, yellow, red
- pedestrian traffic light 1 (nourth-south): greed, red, button
- pedestrian traffic light 2 (east-west): greed, red, button

How It Works?
One car traffic light is green for 5 seconds, then it turns yellow for 2 seconds, and then it turns red. After 1 second, the other car traffic
light turns green for 5 seconds, then yellow for 2 seconds, then red. Then, the other car traffic light turns green after 1 second, and 
the cycle repeats.
This can be represented as follows:
- car traffic 1:
  green: 5 seconds
  yellow: 2 seconds
  red

  1 second

- car traffic 2:
  green: 5 seconds
  yellow: 2 seconds
  red

  1 second

- car traffic 1:
  green: 5 seconds
  .
  .
  and so on..

When a pedestrian presses a button, if the car traffic light was green, the pedestrian traffic light turns green for 2 seconds, then it turns red again,
and, within the same 2 seconds, the car traffic light turns red, then it turns green again. If the button was pressed after the car traffic light has been
green for 3 seconds, for example, then when it turns red then turns green again, it will be green for 2 seconds in order to complete the 5 seconds, then
it will turn yellow.
This can be represented as follows:
- car traffic 1:	- pedestrian traffic 1:
  green: 3 seconds	  red

  button pressed
 
  red: 2 seconds	  green: 2 seconds
  green: 2 seconds	  red
  yellow: 2 seconds
  .
  .

Note that when a button is pressed the car traffic light is interrupted only if it was greean. Obviously, only one of the two traffic lights can be green 
at a specific time. This means that if the two buttons of the two pedestrian traffic lights are pressed at the same time, the one associated with the car
traffic light that is green at that time is the only one that will be serviced.

When a button is pressed, it will be locked for three seconds. This leads to two additional features in the system. The first one is that if one button is
pressed then pressed again whithin 2 seconds, nothing will change because within the 2 seconds, the pedestrian traffic light is already green. 
Additionally, the system will not interrupt the car traffic before at least 1 second passes after the end of the period of the last pedestrian crossing.

Finally, when the system changes its state, it sends its current state. The states of the system are as follows: 
CARS NORTH SOUTH: car traffic light 1 is either green or yellow
CARS EAST WEST: car traffic light 2 is either green or yellow
PEDESTRIAN NORTH SOUTH: pedestrian traffic light 1 is green
PEDESTRIAN EAST WEST: pedestrian traffic light 2 is green

 






