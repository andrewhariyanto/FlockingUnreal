# FlockingUnreal
Hello! This is a flocking simulator made in C++ in Unreal 5.1

Boid's Algorithm has three core rules:
1. Separation: agents close to each other will repel
2. Alignment: agents will tend to go in the same direction as other near agents
3. Cohesion: agents will tend to go to the average position of other near agents

In addition to these three rules I added three more:
1. Limit bounds: I set the bounds to be -1000 to 1000 for X, Y, Z axes. Once it passes the bounds, the agents will gradually come back within the bounds
2. Wind: I set the wind to be (0.1, 0, 0). The agents will move to the right by 0.1 every frame in addition to the resultant vector from the other rules
3. Limit velocity: makes sure the agent does not go too fast. The implementation of this is found in each agent class not in the flocking manager

To use:
1. Download the repo
2. Open the Flocking.uproject file. It will ask you to rebuild upon first time opening. Needs Unreal 5.1
3. Recompile C++ code if it does not show in the content drawer
4. Press play
5. If agents do not show, sometimes the static mesh of the agents does not appear (not sure why). Set the static mesh in the FlockingGameModeBase blueprint

Here is a link to a gameplay video:
https://youtu.be/WoZC5W719ZM
