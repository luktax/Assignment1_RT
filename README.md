This project implements a ROS2 workflow that manages two turtles in Turtlesim using three custom nodes:

spawn_turtle – spawns a second turtle

ui_node – user interface node to control each turtle individually

distance_node – monitors the distance between turtles and checks collision with the walls

1. Spawn Turtle Node

The spawn_turtle node is implemented as a Python package.
Starting from the provided file, the node uses the /spawn service of Turtlesim to create a second turtle in the simulation environment.

2. UI Node (User Interface Node)

The ui_node is implemented as a C++ package and provides a simple command-line interface to manually control the two turtles.

Main Features

Two publishers on the cmd_vel topics:

/turtle1/cmd_vel

/turtle2/cmd_vel

A timer callback triggered every 50 ms

An internal counter incremented at each callback execution

20 iterations ≈ 1 second

Every second, the node:

asks the user which turtle to control (1 or 2)

asks for linear and angular velocity

publishes the velocity continuously for 1 second

Input Handling

The node repeatedly prompts the user until valid input is provided:

1 or 2 to select the turtle

Numerical input for linear and angular velocities

The cycle repeats indefinitely, allowing the user to update commands in real time.

3. Distance Node

The distance_node implements position checks by monitoring:

the distance between the two turtles

the distance of each turtle from the walls

Components

Two subscribers:

/turtle1/pose

/turtle2/pose

One publisher on /distance to publish the distance between the turtles

Two publishers on each turtle's /cmd_vel to stop them when a safety condition is triggered

A timer callback every 50 ms

Behavior

Each subscriber callback stores the current pose of its turtle.

The timer callback:

computes the distance between the turtles

publishes the value on the /distance topic

checks the following conditions:

turtle-to-turtle distance is below a defined threshold

a turtle is too close to a wall

If a condition is met:

a Twist message with zero velocities is published

both turtles are stopped immediately if they are too close

one turtle stop if it reaches the walls

Error

When the turtle reaches a wall, the stop message is not sent immediately, 
so the real position of the turtle is already inside the critical area.
This doesn't allow to move the turtle anymore because the check will immediately be satisfied. 
It can be simply corrected by forcing the turtle to step back outside the area,
before allowing it to move again. (NOT REQUIRED BY THE ASSIGNMENT).
