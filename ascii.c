#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>

int main(){
    char imgname[256],ch;
    //$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.
    char light[70]="$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    int filesize,widths[4],width=0,padding, height=0,heights[4], binary[16]={0,0,0,0,0,0,0,0},intnothing,end;
    float a,r,g,b,nothing;
    double val;
    FILE *ptr, *tptr= fopen("temp.txt","w+"), *optr=fopen("output.txt","w+"), *fptr=fopen("ascii.txt","w");

    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);

    scanf("%s", imgname);
    strcat(imgname,".bmp");
    system("cls");

    if(!(ptr=fopen(imgname,"rb"))){
        puts("Invalid file name");
        system("pause");
        return 0;
    }

    fseek(ptr,0,SEEK_END);
    filesize= ftell(ptr);
    printf("File size(bytes): %d\n",filesize);
    fseek(ptr,0,SEEK_SET);

    unsigned char test[2];
    while((fread(test,2,1,ptr) == 1))  //ifp is input file pointer
        {
          int first_bit = test[0] & 0x80;

          if(test[0]<10){
            fprintf(tptr,"0%d ",test[0]);
          }
          else{
            fprintf(tptr,"%d ",test[0]);
          }

          if(test[1]<10){
            fprintf(tptr,"0%d ",test[1]);
          }
          else{
            fprintf(tptr,"%d ",test[1]);
          }
    }
    printf("\nImage scanning complete...");
    fclose(ptr);

    fseek(tptr,0,SEEK_SET);
    for(int i= 0; i< 18;i++){
        fscanf(tptr,"%d ",&intnothing);
    }
    fscanf(tptr,"%d %d %d %d",&widths[0],&widths[1],&widths[2],&widths[3]);

    if(widths[2] >0|| widths[3] >0){
        printf("Image inputted is too big");
        system("pause");
        return 0;

    }
    else if(widths[0]== 0){
        for(int i=0, j=7; i< 8;i++){
            binary[j]=widths[1]%2;
            widths[1]=widths[1]/2;

            if(j!=0){
                j--;
            }
        }
        for(int i=0, j=15; i< 8;i++){
            binary[j]=widths[2]%2;
            widths[2]=widths[2]/2;

            if(j!=8){
                j--;
            }
        }
        for(int i=0;i<16;i++){
            width+= binary[i]*pow(2,15-i);
        }
    }
    else if(widths[0]>0){
        width= widths[0];
    }

    if(width%4!=0){
        padding= width%4;
    }
    else{
        padding= 0;
    }

    fscanf(tptr,"%d %d %d %d",&heights[0],&heights[1],&heights[2],&heights[3]);

    if(heights[2] >0|| heights[3] >0){
        printf("Image inputted is too big\n");
        system("pause");
        return 0;

    }
    else if(heights[0]== 0){
        for(int i=0, j=7; i< 8;i++){
            binary[j]=heights[1]%2;
            heights[1]=heights[1]/2;

            if(j!=0){
                j--;
            }
        }
        for(int i=0, j=15; i< 8;i++){
            binary[j]=heights[2]%2;
            heights[2]=heights[2]/2;

            if(j!=8){
                j--;
            }
        }
        for(int i=0;i<16;i++){
            height+= binary[i]*pow(2,15-i);
        }
    }
    else if(heights[0]>0){
        height= heights[0];
    }

    if(width >115 || height>115){
        printf("\nImage size too big\n");
        system("pause");
        return 0;
    }

    printf("\nWidth: %d \nHeight: %d \nPadding: %d",width,height,padding);
    fseek(tptr,0,SEEK_SET);

    for(int k=0;k<54;k++){
        fscanf(tptr,"%d",&nothing);
    }

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            fscanf(tptr,"%f %f %f",&b,&g,&r);
            a=(b+g+r)/3;
            fprintf(optr,"%.2f ",a);
        }
        fprintf(optr,"\n");
    }

    printf("\nLight values calculated...");

    fclose(tptr);

    for(int i=0;i<height;i++){
        fseek(optr,0,SEEK_SET);
        for(int k=height-i-1;k>0;k--){
            fscanf(optr, "%*[^\n]\n");
        }
        for(int j=0; j<width;j++){
            fscanf(optr,"%lf ",&val);
            fprintf(fptr,"%c%c",light[(int)floor((val/255)*69)],light[(int)floor((val/255)*69)]);
        }
        fprintf(fptr,"\n");
    }

    fclose(optr);
    fclose(fptr);
    printf("\nASCII image completed...\n");
    system("pause");
    system("cls");
    system("color f0");
    system("type ascii.txt");
    system("pause");

    return 0;
}
