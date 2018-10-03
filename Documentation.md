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

When the program writes the AI database to file, the program will automatically save in the syntax format above.

**AI Communication**

The user first inputs text to the AI. If a text begins with "/", the text is treated as a command. The two commands are "/exit" and "/chat". "/exit" will exit the program and save the AI database to file. "/chat" enables the AI to initiate communication (discussed in later section). Other command formats and empty strings are considered syntax errors. Any other text input is considered as dialogue.

When the user inputs dialogue, it is compared to all existing templates. The AI searches the best template match for the dialogue. If a match is found, a randomly selected response of that particular template's object is output to the user. The dialogue is then saved as a template of that object if it does not exist. If a suitable match is not found, a new object is created for the new template. The AI then switches to record input and prompts the user for a response for that particular object. If the user inputs a command or empty string, the AI rejects the response and switches back to regular chat input.

If the user inputs the "/chat" command, the AI randomly outputs a template if the database is not empty. If the database is empty, the command is terminated. After the template is outputted, the AI switches to record input. The user can then input a response that is stored in the template's object's list of responses. If the user inputs a command or empty string, the AI rejects the response and switches back to regular chat input.
