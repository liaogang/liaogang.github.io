//
//  main.cpp
//  getHtmlTitle
//
//  Created by liaogang on 16/7/19.
//  Copyright © 2016年 liaogang. All rights reserved.
//

#include <iostream>

void usage()
{
    printf("usage: \n");
    printf("getHtmlTitle [filename]\n");
}

int main(int argc, const char * argv[]) {
    
    if (argc == 2)
    {
        FILE *file = fopen( argv[1], "r");
        if (file)
        {
//            const int titleLen = sizeof(title)/sizeof(title[0]);
            char *ptitle = NULL ;
            int bufOffset = 0;
            const int length = 256 ;
            char buf[length];
            
            while ( ptitle == NULL)
            {
                const char title[] = "<title>";
                const char title2[] = "</title>";
                
                
                size_t readed = fread(buf+bufOffset,sizeof(buf[0]),length - bufOffset, file);
                if (readed > 0)
                {
                    ptitle = strstr(buf, title);
                    if (ptitle)
                    {
                        int ptitleLen = buf + length - ptitle; // in buf
                        
                        // copy to head of buf
                        memcpy(buf  ,ptitle , ptitleLen );
                        
                        // fill the left ended
                        fread( buf + ptitleLen , sizeof(char), ptitle - buf , file);

                        
                        
                        char *ptitle2 = strstr( buf + strlen(title) , title2);
                        if (ptitle2)
                        {
                            char show[256] = {0};
                            
                            int i = strlen(" - 「ONE · 一个」");
                            
                            strncpy(show , buf+strlen(title)  , ptitle2 - buf - strlen(title) - i );
                            
                            
                            printf("%s\n",show);
                        }
                        
                        break;
                    }
                    else
                    {
                        bufOffset = 6; // title's length - 1
                        memcpy(buf , buf+length-bufOffset,  6);
                    }
                }
                else
                {
                    printf("Can not find `title` tag at %s.\n",argv[1]);
                    break;
                }
            }
            
            
            fclose(file);
        }
        
    }
    else
    {
        usage();
    }
    
    
    
    return 0;
}
