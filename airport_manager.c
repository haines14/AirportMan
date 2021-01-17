#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport_manager.h"
void InitializeAirline(Airline *airline, int maxAirportsN){
airline->airports = malloc(sizeof(Airport *)*maxAirportsN);
airline->numAirports = 0;
airline->maxAirports = maxAirportsN;
//Possibly a for loop to initalize everything to null
}
int AddAirport(Airline *airline, const char* name){
	//Check if their are currently no Airports for string compare check
	if (name == NULL){
		return 0;
	}
	
	if (airline->numAirports != 0){
		
	for (int i = 0; i < airline->numAirports;i++){
		if (strcmp(name,airline->airports[i]->name)==0){
			return 0;
		}
	}
}
	
	//Check to see if one away from max airports
	if (airline->numAirports ==  airline->maxAirports){
		Airport** temp = realloc(airline->airports,sizeof(Airport *)*airline->maxAirports*2);
		airline->maxAirports*=2;
		airline->airports = temp;
	}
	
		airline->airports[airline->numAirports] = (Airport *)malloc(sizeof(Airport));
		airline->airports[airline->numAirports]->name = strdup(name);
		airline->airports[airline->numAirports]->destinations = NULL;
		airline->airports[airline->numAirports]->numDestinations = 0;
		airline->numAirports++;
		return 1;
	
	}
Airport *FindAirport(Airline *airline,const char* name){
	if (!airline){
		return NULL;
	}
	if (name == NULL){
		return NULL;
	}
	if (airline->numAirports == 0){
		return NULL;
	}
	for (int i = 0; i < airline->numAirports;i++){
		if (strcmp(airline->airports[i]->name,name)==0){
			return airline->airports[i];
	
	}
	}
		


	return NULL;




}
int AddFlight(Airline *airline, const char *origin_name, const char* dest_name){
	
	Airport *from = FindAirport(airline,origin_name);
	Airport *to = FindAirport(airline,dest_name);
	if (strcmp(origin_name,dest_name)==0){
		return 0;
}
	if (!from){
		return 0;
	}
	if (!to){
		return 0;
	}
	
			
	//airport has at least one destination
	if (from->numDestinations != 0 ){
		for (int i = 0; i < from->numDestinations;i++){
			if (strcmp(from->destinations[i]->name,dest_name)==0){
			//This flight exists
				return 0;
			}
		}
	//
	
		//more then one destination, flight doesn't already exist
		from->destinations = realloc(from->destinations,sizeof(Airport *)*(from->numDestinations+1)); 
//		from->destinations[from->numDestinations] = malloc(sizeof(Airport));
		from->destinations[from->numDestinations] = to;
//		from->destinations[from->numDestinations]->name = strdup(to->name);
//		printf("Printing right now %s\n",from->destinations[from->numDestinations]->name);
		from->numDestinations++;
		
		return 1;
	}
	else{
	//No destinations currently 
	from->destinations = malloc(sizeof(Airport *));
//	from->destinations[from->numDestinations] = malloc(sizeof(Airport)); //This seems like I don't need int
//	from->destinations[from->numDestinations]->name = strdup(dest_name);
	from->destinations[from->numDestinations] = to;
//	from->destinations[from->numDestinations]->name = strdup(to->name);
	//printf("%s",from->destinations[0]->name);
	from->numDestinations++;
	return 1;
	}








return 0;
//This was from a previous attempt that went south very quickly	
	//if origin name is found in numAirports
	
//Both of these should be covered in other cases but I don't know 
		//Not having test cases makes this harder to debug
		//We should be adding now so now we check destinations
		
		//Using FindAirport now I will have access to the place I need 
		//Somewhere in this case we will use numAirports++;
		//Case where dest and origin are found, but not checked to be already a flight
		//No clue how to check the flight probably the destionations array and see if the dest name is already found
		
}
int PrintFlightsFromAirport(Airline *airline, const char *origin_name){
//	Airport *sc = FindAirport(airline,origin_name);
//	for (int i = 0; i < airline->numAirports;i++){
//		printf("%s\n",airline->airports[i]->name);
//	}	
//	printf("done here");
	//check is used to see if airport name exists
	Airport *check = FindAirport(airline,origin_name);
		if (!check){
			return 0;
	}
	for (int i =0 ; i< airline->numAirports;i++){
		if (strcmp(airline->airports[i]->name,origin_name)==0){
			int star = 0;
			if (airline->airports[i]->numDestinations == 0){
				return 1;
			}
			//printf("%s",airline->airports[i]->destinations[star]->name);
			while (star < airline->airports[i]->numDestinations){
				printf("%s\n",airline->airports[i]->destinations[star]->name);
				star++;
			}
			
		}	
	}
	return 1;
}
int PrintFlightsToAirport(Airline *airline, const char *dest_name){
	Airport *likeStart = FindAirport(airline,dest_name);
	if (!likeStart){
		return 0;
		}
	for (int i =0 ;i < airline->numAirports;i++){
		Airport *temp = airline->airports[i];
		if (temp->numDestinations != 0){
			for (int w =0 ; w < temp->numDestinations;w++){
				if (strcmp(temp->destinations[w]->name,dest_name)==0){
					printf("%s\n",temp->name);
				}
			}
		}
	}
	return 1;

}
void PrintAirlineAsMatrix(Airline *airline){
	if (!airline){
		return;
	}
	for (int i = 0; i < airline->numAirports;i++){
		Airport *curr = airline->airports[i];
		for (int j = 0; j < airline->numAirports;j++){
					
			int flag = 0;
			Airport *next = airline->airports[j];
			if (curr->numDestinations != 0){
			for (int a =0; a < curr->numDestinations;a++){
				if (curr->destinations != NULL){
				if (curr->destinations[a]->name != NULL){
				if (strcmp(curr->destinations[a]->name,next->name)==0){
					flag = 1;
				}
				}
			}
			}
			printf("%d",flag);
		}
	}
	printf("\n");
}

	//this looks easy but long
}
int HasDirectFlight(Airline *airline, const char *origin_name, const char *dest_name){
	Airport *start = FindAirport(airline,origin_name);
	Airport *end = FindAirport(airline,dest_name);
	if (!start){
	return 0;
	}
	if (!end){
		return 0;
	}
	if (strcmp(start->name,end->name)==0){
		return 0;
	}
	if (start->numDestinations != 0){
		for (int i =0 ; i < start->numDestinations;i++){
			if (start->destinations[i] == end){
				return 1;
			}
			//Not for sure which works so I am using both
			if (strcmp(start->destinations[i]->name,end->name)==0){
				return 1;
			}
		}
	}
	return 0;
	}
int HasOneStopFlight(Airline *airline, const char *origin_name, const char *dest_name){
	Airport *lastOne = FindAirport(airline,origin_name);
	Airport *lastOneEnd = FindAirport(airline,dest_name);
	if (!lastOne){
		return 0;
	}
	if (!lastOneEnd){
		return 0;
	}
	if (strcmp(lastOne->name,lastOneEnd->name)==0){
		return 0;
	}
	if (lastOne == lastOneEnd){
		return 0;
	}
	for (int i =0 ; i < airline->numAirports;i++){
		Airport *temp = airline->airports[i];
		if (temp == lastOne){
			if (temp->numDestinations != 0){
				for (int k = 0; k < temp->numDestinations;k++){
				Airport *find = FindAirport(airline,temp->destinations[k]->name);
				if (find->numDestinations != 0){
					for (int l = 0; l < find->numDestinations;l++){
						if (find->destinations[l] == lastOneEnd){
							return 1;
						}
					}
				}
				}
			}
}
}
	return 0;
}
void DeleteAirline(Airline *airline){
	for (int i = 0; i < airline->numAirports;i++){

			free(airline->airports[i]->name);
			if (airline->airports[i]->numDestinations != 0){
				free(airline->airports[i]->destinations);
			}
			
			free(airline->airports[i]);
		}

	free(airline->airports);
	}	
void GuaranteeOneStop(Airline *airline){
        for (int i =0 ; i < airline->numAirports;i++){
                for (int j =0 ; j < airline->numAirports;j++){
                       if (strcmp(airline->airports[i]->name,airline->airports[j]->name) != 0){
                           int s = HasDirectFlight(airline,airline->airports[i]->name,airline->airports[j]->name);
                           int thatWasEasy = HasOneStopFlight(airline,airline->airports[i]->name,airline->airports[j]->name);
                           if ((s != 1) && thatWasEasy != 1){
                                  AddFlight(airline,airline->airports[i]->name,airline->airports[j]->name);
                           }
                       }
                }
        }
}

