#Code Revision
Write an application which simulates the code revision process for a software application, as follows:

The information about the development team is read from a text file. Each member of the team (Programmer) has a name (string), a number of revised files (int) and the total number of files they must revise (int). This file is manually created and it is read when the application starts.
Information about the source code files of the software application is stored in another file. Each SourceFile has a name (string), a status (one of revised or not_revised), its creator – the programmer who created it and the reviewer – the programmer who revised it. These are read when the application starts.
[1.5p] When the application is started, a new window is created for each programmer, as follows:
The window title is the programmer’s name.
All source files are displayed within a single table component with a header. Each file is displayed on its own table row. File name, status, creator and reviewer are displayed in separate columns. The table is sortable by each of its columns. Initially, table rows are sorted by file name.
Information for unrevised files is bolded; rows showing revised files have a green background.
The window includes two labels: one with the number of files alraedy revised by the programmer and one with the number of files they still have to revise.
[1.5p] Any programmer can add a new file by entering the file name into a text field and pressing an “Add” button. The file’s creator is automatically set as the programmer who added it and its status is not_revised. This operation fails if the file name is empty or if there is another file with the same name. The user is informed if the operation failed .
[2p] Programmers can revise files by selecting the file and pressing the “Revise” button:
The button is enabled only if the status of the selected file is not_revised and the revising programmer is not the file's creator.
Revising a file switches its status to revised and the name of its reviewer is automatically set to the name of the programmer who revised it.
When a programmer revises a file, their revised file count increases and the number of files they still have to revise decreases. When they reach the total number of files they must revise, a “Congratulations” message is shown.
[1.5p] A separate window shows statistics about the programmers and revised files: for each programmer - the name and a circle with a radius proportional with how many files they have revised. For programmers who have reached the total number of files they must revise, the name and circle will be shown in blue.
[2.5p] Any modifications will automatically update the tables displayed across all programmer windows and the statistics window.
Observations
Not reading data from files incurs a 50% penalty from the score for functionalities 3, 4 and 5.
You may use programmers.txt and sources.txt as input files
Use of layered architecture is mandatory.
default 1p.
