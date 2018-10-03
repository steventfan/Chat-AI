# **Chat AI**

## How To Use

1. Run "make" in the command line
2. Ensure *inputs/* folder contains a text file with the appropriate name (default *data.txt*) that follows the AI initialization protocol (discussed in next section)
3. Run bin/chat in the command line

**AI Initialization Protocol**

The AI initializes its database from the text file *data.txt* in the *inputs/* folder. The text file *data.txt* must follow the correct syntax format in order to ensure proper initialization of data. The AI functions by comparing user inputs with templates and generating the appropriate response. The text file *data.txt* is thus initialized using the following format:

*`<templates>`*\
`-`\
*`[responses]`*\
`*`

Repeat for each template and response object.

**Note:**\
\<\> denotes required parameters\
\[\] denotes optional parameters\
Each parameter can have multiple lines of text.

When writing the AI database to file, the program will automatically save in the syntax format.
