# CodeSamplesUE
This is a showcase of a few UE4 code samples from work I've made in the past years. It is reduced and intended to work together as if they were part of an Unreal Engine project that we'll refer to as YOURPROJECT. Custom classes could use this codename or CUSTOM, depending on what I showcase.

# The files act as if they formed part of the same project
Read through the files to find their relations and how they use the other 'features' of this project. 
- There is a Game Mode that spawns a Manager Class and allows binding to a generic delegate of itself. 
- There is a CustomActor class that is registered by this Manager Class and can also answer to the delegate of the Game Mode.
- There is a Custom Library that has a few utilities from Sound to Math, and can be accessed from any class easily. The CustomActor does it.
- There is an example of a Header File of the project with it's enumerators, structures, and definitions of Log categories or Macros.
- There is a Custom Module that could be applied externally to the Content in your Project solution (.sln).
