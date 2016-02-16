int findbit(char d, char a)
{
        int b;
        int c;

        a = a ^ d;
        for(b = 6; b >= 0; a = a << 1){
                if(0100 & a){
                        //printf("1");
                        return(b);
                }
                else{ ;
                        //printf("0");
                }
                b--;
        }
        return 0;
}

