Contributers:
- Arel Sharon 323012971
- Matan Amichai 315441972


Bonus:
- We included a bonus.txt file in the root directory
How to build?
- We included a CMakeList.txt File, you may use it to build 
- We tested mainly on Ubuntu22 WSL, MacOS
- **Windows isn't supported!**

Solution approach:
- Select an algorith and create a configuration for it.
    - Currently always selects the Naive one as there aren't anymore avalible
- Create a "House cleaner" which will run VacuumSimulator and save the results
    - Get path to file with house config
    - Get algorith configuration

    - Parse the input file into a VacuumSimulator 
        - Create the Battery keeps track of batterly levels
        - Create house that keeps the layout of house (After postprocessing)
        - Determine a starting position using house

    - run VacuumSimulator, with algorithm configuration
        - Create fresh record 
        - Create from configuration a fresh instance of algorithm owned by this run
        - while shouldn't terminate (Either because stuck, is succesful or reached max steps)
            - Step algorithm 
                - Returns move direction
            - Apply algorithm move
                - Determine actions to take like, charge, activate, move to direction etc 
            - Document it in a record
        - Return record

    - Save the results (seperate from running)
- House cleaner prints the output file location(which is determined by the format)



Input File format:
The input file is seperated into 2 segments
- Segment 1
First 2 lines of the file.
First line is the max steps allowed to run
Second line is the max battey steps.
- Segment 2
House representation, each char here represents a house locations up until the end of the file
x - The charging station
w - A wall either internal, external, a corridor etc
0-9 - Any digit a house tile with this amount of dirt on it
Any other char - shouldn't be used but will be considered as a wall
Example format:
10
5
wwww
w89w
wx9w
wwww

Some irecoverable violations of format:
-No charging station.
-Multiple charging stations.
-Negative or missing any of first 2 rows
-Malfromed first 2 rows (as defined by stoi)
Some recoverable violations:
-Invalid chars considered as walls
-Outer perimiter will always be filled with minimal wall to ensure enclosure
-Empty Lines(not spaces, empty) before after or during representation will be ignored (Not counted as walls just removed)

Output file format-
Action can be either North,South,East,West,CLEANING,CHARGING
Total steps: count of all applied steps algorithm yielded
Dirt left: self explanatory
Battery exhausted/Mission success Either No or Yes defined by the assigment

<<Example output>>

Cleaning process completed.
All The Steps that performed by the vacuum cleaner: 
Moved to: (2, 2), Action: North, Battery: 4
Moved to: (2, 2), Action: CLEANING , Dirt: 25, Battery: 3
Moved to: (2, 2), Action: CLEANING , Dirt: 24, Battery: 2
Moved to: (2, 2), Action: CLEANING , Dirt: 23, Battery: 1
Moved to: (3, 2), Action: South, Battery: 0
Moved to: (3, 2), Action: CHARGING, Battery: 0
Moved to: (3, 2), Action: CHARGING, Battery: 0
Moved to: (3, 2), Action: CHARGING, Battery: 0
Moved to: (3, 2), Action: CHARGING, Battery: 1
Moved to: (3, 2), Action: CHARGING, Battery: 1

Total steps: 10
Amount of dirt left: 23
Battery exhausted: No
Mission success: No

<<End example output>>

