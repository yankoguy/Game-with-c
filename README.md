# Game-with-c
A game i made with c and sdl

I made a simple 2d game with c and SDL. The character is a square which you can move by press WASD, aim with the mouse and shoot with space. There are also texts at the top of the screen. You fight with waves of enemies: after killing a wave a timer will start, when it reaches 5 sec another wave spawn. There are 2 types of enemies: exploding and shooting. Exploding - run to the player and when they collide they change color. If the collision takes several seconds the enemy changes its color to black and then explored in a radius. Shooting - aim and shoot on you. They are also green squares which give ammo and red ones which give health. They are 2 types of bullets: normal and shocking: normal - deal dmg no side affects shock - deal dmg and shock enemy for 0.5 sec (he cant move and shoot)