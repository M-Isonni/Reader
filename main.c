#define SDL_MAIN_HANDLED
#include "ui.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

int window_closed(uiWindow *window,void *data)
{
    uiQuit();
    return 1;
}

typedef struct file_struct{
    uiWindow *uiWindow;
    char *text;
    uiMultilineEntry *entry;
}file_struct_t;

void OpenFileMgr(uiButton *button, void *data)
{
    //array to save text inside the file
        char text[4096];
        memset(text,0,4096);
        file_struct_t *file=data;
        //get the file path from open file manager
       char *path=uiOpenFile(file->uiWindow);
      FILE *file_reader;
      //open the file and get a placeholder at the start of it
        int error=fopen_s(&file_reader,path,"r"); 
        if(error!=0)
        {
            SDL_Log("error n.: %d",error);
        }
        //get text inside the file and put it in the array of char    
        fgets(text,4096,file_reader);      
       //print in multiline entry the content of text
       uiMultilineEntrySetText(file->entry,text);
       fclose(file_reader);      
}
       

int main(int argc, char **argv){

    uiInitOptions options;
    memset(&options,0,sizeof(uiInitOptions));

    uiInit(&options);

    uiWindow *window = uiNewWindow("window",800,600,0);

    uiWindowOnClosing(window, window_closed,NULL);

    uiBox *vertical = uiNewVerticalBox();    
    uiButton *button = uiNewButton("click me");     
    uiBoxAppend(vertical,uiControl(button),0);     
    uiMultilineEntry *entry = uiNewMultilineEntry();   
    uiBoxAppend(vertical,uiControl(entry),0); 

    uiWindowSetChild(window, uiControl(vertical));

    uiControlShow(uiControl(window));

    file_struct_t file_struct;
    file_struct.uiWindow=window;    
    file_struct.entry=entry;

    uiButtonOnClicked(button,OpenFileMgr,&file_struct);
    
    uiMain();

    return 0;
}