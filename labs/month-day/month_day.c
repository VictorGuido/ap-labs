#include <stdio.h> include <stdlib.h>
void month_day(int year, int yearday){ int diasM[12] = {31, 28, 31, 30, 
        31, 30, 31, 31, 30, 31, 30, 31}; char *meses[12] = {"Jan", 
        "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", 
        "Nov", "Dic"}; int contador; int diaM=0; int Mes=0; int diaT=0; 
        int diaTA=0; int dif=0; if( year % 4 == 0){
                diasM[1]=29;
        }
        for(int i =0; i<12;i++){ if(diaT > yearday){ dif = yearday - 
                diaTA; printf("%s %d, %d", 
                meses[Mes-1], dif, year); break;
            }
            else if(yearday <= 31){ diaM = yearday; Mes=0;
                //posible return
                printf("%s %d, %d", meses[Mes], yearday, year);
                //printf("%s %d, %d\n", months[cont], tmp_yday, *pyear);
                break;
            }
            else{ diaTA= diaT; diaT = diaT + diasM[i]; Mes++;
            }
            
        }
}
int main(int argc, char* argv[]) { int year = atoi(argv[1]); int day = 
	atoi(argv[2]); int* p_year = &year; int* p_day = &day; 
	month_day(year, day); return 0;
}
