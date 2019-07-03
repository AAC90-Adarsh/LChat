# LChat - A simple messaging system for Linux/Unix servers
### Written by Adarsh Cavale

## Overview
This is a small project that uses named pipes, or FIFO's, to transmit and receive messages. I have a little free time at work in between projects and I decided to start a small project of my own! It started out with my frustration with the bugs in Skype's messaging system. We use it at work and it frequently drops messages and sends messages prematurely. With my program, I can communicate easily between my co-workers without having any of Skype's issues.

There are a few components to this project: 
 - The reader program, which reads messages from other users. This is more of an inbox, since messages from other users will be posted here. 
 - The writer program, which allows you to write to another person's inbox. You can write to as many people's inboxes as you want!
 - The fifo directory (`chatroom/fifos/`) stores all of the FIFO's for every user. If there are 10 people using the LChat, create 10 FIFO's in `chatroom/fifos` labeled by name and reference them when running `reader.c` and `writer.c`.

## Some features
#### (This will be added to later)
- Ability to not only have one-on-one messaging, but you also can receive many messages at once to your inbox.
- The joint program structure gives you the ability to read messages in your inbox (`reader.c`) from anyone while sending messages to multiple people.
- Pair LChat with TMUX and make the most out of your experience.

## To install and run
#### (Will come up with a script in the future to make it even easier)
1. First, clone my repository.
   - Example: `mkfifo John` will create a fifo called `John`. Make sure this is in the `chatroom/fifos/` directory!
2. Make the executables by running `make`. This will create the two executables `reader` and `writer`.
   - If you wish to add on to my code and want to remake the executables, make your changes to the source code and run `make clean`. This will get rid of only the executables `reader` and `writer`. When you are ready to test, just run `make` again. The `chatroom/fifos` directory will remain intact. 
     - Please create a feature branch if you wish to push any changes or improvements to the repository. I would love to see what changes can be made.
3. (optional, but will be a lot easier for you) Open up TMUX with `tmux` and create a window pane each for `reader` and `writer`.
   - Look up tmux syntax if you are confused. It is a very helpful tool with my programs and in general.
4. In one window, run `./reader <name of your FIFO>`. This will open up a reader for your FIFO so that you can see who is writing messages to you. This can be multiple people as well. 
   - Technically, you can read anyone's FIFO, not just yours. This will be an issue I will try and fix in the feature.
5. In the other window, run `./writer <name of your FIFO> <name of the person's FIFO you want to write to>`. This program requires two arguments. Otherwise, a segmentation fault will occur. I will make a change to handle the seg fault in a future release. 
6. Then you're all set! You can now send messages to your friend who's currently working on the same Linux or Unix VM, server, or machine you're shelling into. This does not work over TCP/IP yet, but I may add TCP/IP socket support in the future For cross-machine support.
   - Using TMUX, you can potentially create `writer`'s to multiple people, all while having one reader that can receive messages from every one of those people.

Thank you for taking the time to check this out! Please make sure to address any issues or any additional features you would like to see in "Issues" and I will do my best to look out for them.
