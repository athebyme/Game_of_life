# :video_game: Game of Life :video_game: 
> Lab №4 on Software Development Tools

# The project was made by:
1. :dolphin: __Ilya Burlak__ ..........[GitHub](https://github.com/IlyaBurlak)
2. :whale: __Anton Bruhov__ .....[GItHub](https://github.com/athebyme)
3. :whale2:__Bogdan Gabov__.....[GitHub](https://github.com/goy1a)
4. :fish:__Ilya Konovalow__....[GitHub]()
----   
## Rules of the game
[Rulse on Wiki](https://ru.wikipedia.org/wiki/%D0%98%D0%B3%D1%80%D0%B0_%C2%AB%D0%96%D0%B8%D0%B7%D0%BD%D1%8C%C2%BB)  

![logo](Gospers_glider_gun.mp4)

+ **The place of action of the game is a plane marked into cells, which can be unlimited, limited or closed.**
+ **Each cell on this surface has eight neighbors surrounding it, and can be in two states: to be "alive" (filled) or "dead" (empty).
The distribution of living cells at the beginning of the game is called the first generation.**
+ **Each next generation is calculated based on the previous one according to the following rules:**
  + *In an empty (dead) cell, which is adjacent to three living cells, life is born;*
  + *If a living cell has two or three living neighbors, then this cell continues to live; otherwise (if there are less than two or more than three living neighbors), the cell dies (“from loneliness” or “from overcrowding”).*
+ **The game ends if:**
  + *Not a single “living” cell will remain on the field;*
  + *The configuration at the next step will exactly (without shifts and rotations) repeat itself at one of the earlier steps (a periodic configuration is added)*
  + *At the next step, none of the cells changes its state (the previous rule applies one step back, a stable configuration is formed)*
## In this work, we have implemented:
### **1) Create a small project board in Trello**
+ *Divided into roles within the team*
+ *Mandatory fixation of all documents, decisions, tasks and other things within the framework of the project.*
+ *maintaining a Git repository with attaching commits in the project management system.*
+ *CI/CD setup*
### **2)Provide an iterative version of project management. With the number of releases**


