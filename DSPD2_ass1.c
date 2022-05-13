#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

typedef struct node_ll{
	int data;
	struct node_ll* next;
}node;

node* createnode(int d){
	node* temp=malloc(sizeof(node));
	temp->data=d;
	temp->next=NULL;
	return temp;
}

void print_programs_enrolled(node* programs){
	node* current=programs;
	int count = 1;
	while(count < 5 && current != NULL)
	{
		if(count == 1 && current->data == 1){
			printf("Yoga ");
		}
		else if(count == 2 && current->data == 1){
			printf("Cardio ");
		}
		else if(count == 3 && current->data == 1){
			printf("Zumba ");
		}
		else if(count == 4 && current->data == 1){
			printf("weightlifting ");
		}
		count++;
		current=current->next;
	}
	printf("\n\n\n");
}

typedef struct member_node_ll{
	int id;
	char name[50];
	int age;
	char gender;
	int booked_today;
	node* enrolled_programs;	//there should be 4 nodes, Yoga, cardio, zumba, weightlifting
	int fee_paid;
	struct member_node_ll *next;
}member_node;

typedef struct trainer_node_ll{
	int id;
	char name[50];
	node* programs;	//there should be 4 nodes, Yoga, cardio, zumba, weightlifting
	int renumeration;
	struct trainer_node_ll *next;
}trainer_node;

member_node* create_member(int Id, char Name[], int Age, char Gender, int Booked_today, node* Programs, int Fee_paid){
	member_node* temp = malloc(sizeof(member_node));
	temp->age = Age;
	temp->booked_today = Booked_today;
	temp->enrolled_programs = Programs;
	temp->fee_paid = Fee_paid;
	temp->gender = Gender;
	temp->id = Id;
	strcpy(temp->name, Name);
	temp->next = NULL;
}

trainer_node* create_trainer(int Id, char Name[], node* Program, int Renumeration){
	trainer_node* temp = malloc(sizeof(trainer_node));
	temp->id = Id;
	strcpy(temp->name, Name);
	temp->programs = Program;
	temp->renumeration = Renumeration;
	temp->next = NULL;
}

member_node* Add_member(member_node* member_list, member_node* new_member){	
	member_node* current = member_list;	//this is the head of the members list
	int stored = 0;
	
	if(current->id == -1){
		member_list = new_member;
	}
	else if(current->id > new_member->id){
		member_list = new_member;
		member_list->next = current;
	}
	else{
		while(current != NULL && current->next != NULL && stored == 0){
			if(current->id < new_member->id && new_member->id < current->next->id){
				member_node* temp = current->next;
				current->next = new_member;
				new_member->next = temp;
				stored = 1;
			}
			current = current->next;
		}
		if(stored == 0){	//is the id is greater than all the pre existing ids
			current->next = new_member;
		}
	}
	
	printf("Successfully added a new member \n");
	printf("the new members information is: \n");
	printf("id = %d, \nname = %s, \nage = %d, \ngender = %c, \n", new_member->id, new_member->name, new_member->age, new_member->gender);
	print_programs_enrolled(new_member->enrolled_programs);
	return member_list;
}


trainer_node* Add_trainer(trainer_node* trainer_list, trainer_node* new_trainer){ 
	trainer_node* current = trainer_list;	//this is the head of the trainer_list
	int stored = 0;
	
	if(current->id == -1){
		trainer_list = new_trainer;
	}
	else if(current->id > new_trainer->id){
		trainer_list = new_trainer;
		trainer_list->next = current;
	}
	else{
		while(current != NULL && current->next != NULL){	//need not do this if their ids are entered in a sorted way
			if(current->id < new_trainer->id && new_trainer->id < current->next->id){
				trainer_node* temp = current->next;
				current->next = new_trainer;
				new_trainer->next = temp;
				stored = 1;
			}
			current = current->next;
		}
		if(stored == 0){
			current->next = new_trainer;
		}
	}
	
	printf("Successfully added a new trainer \n");
	printf("the new trainers information is: \n");
	printf("id = %d, \nname = %s \n", new_trainer->id, new_trainer->name);
	//print_programs_enrolled(new_trainer->programs);
	return trainer_list;
}


typedef struct slot_ll{
	int member_id;
	int trainer_id;
	int time_slot;
	int req_program; //1- yoga, 2- cardio; 3- zumba; 4- weightlifting
	char timestamp[70];
	//trainer_node* free_trainers_list;
	struct slot_ll* next;
}slot;

typedef struct ll_2d_slot{
	slot* slot_node;
	struct ll_2d_slot* next;
}ll_2d_node;

ll_2d_node* creatnode_2d_ll(slot *n){
	ll_2d_node* temp=malloc(sizeof(ll_2d_node));
	temp->slot_node = n;
	temp->next=NULL;
	return temp;
}

slot* create_slot_node(int Member_id, int Trainer_id, int Time_slot, int Req_program, char Timestamp[]){
	slot* temp=malloc(sizeof(slot));
	temp->member_id = Member_id;
	temp->trainer_id = Trainer_id;
	temp->time_slot = Time_slot;
	temp->req_program = Req_program;
	strcpy(temp->timestamp , Timestamp);
	temp->next = NULL;
	return temp;
}

trainer_node* Search_trainer(trainer_node* trainer_list, trainer_node* trainer, int key_field){
	trainer_node* current = trainer_list;
	trainer_node* return_trainer_list;
	int found = 0;
	if(key_field == 1){
		while(current != NULL && found == 0){
			if(current->id == trainer->id){
				printf("id = %d, \nname = %s \n", current->id, current->name);
				print_programs_enrolled(current->programs);
				//print the fees paid as well
				return_trainer_list = current;
				found = 1;
			}
			current = current->next;
		}
	}
	else if(key_field == 2){
		trainer_node *return_trainer_list, *current_return_trainer_list;
		while(current != NULL){
			if(strcmp(current->name, trainer->name) == 0){
				printf("id = %d, \nname = %s \n", current->id, current->name);
				print_programs_enrolled(current->programs);
				//print the fees paid as well
				if(return_trainer_list == NULL){
					return_trainer_list = current;
					current_return_trainer_list = return_trainer_list->next;
				}
				else{
					current_return_trainer_list = current;
					current_return_trainer_list = current_return_trainer_list->next;
				}
			}
			current = current->next;
		}
	}
	else if(key_field == 3){
		trainer_node *return_trainer_list, *current_return_trainer_list;
		int count = 0;
		while(current != NULL){
			node *current_programs = trainer->programs;
			while(current_programs != NULL && current->programs != NULL){
				if(current_programs->data == current->programs->data){
					count++;
				}
				current_programs = current_programs->next;
				current->programs = current->programs->next;
			}
			if(count == 4){
				printf("id = %d, \nname = %s \n", current->id, current->name);
				print_programs_enrolled(current->programs);
				if(return_trainer_list == NULL){
					return_trainer_list = create_trainer(current->id, current->name, current->programs, current->renumeration);
					current_return_trainer_list = return_trainer_list;
				}
				else{
					current_return_trainer_list->next = create_trainer(current->id, current->name, current->programs, current->renumeration);;
					current_return_trainer_list = current_return_trainer_list->next;
				}
			}
			count = 0;
			current = current->next;
		}
	}
	// do we have to this for renumeration?
	return return_trainer_list;
}

//creating the kinda 2d linked list to store the schedule
ll_2d_node* create_schedule_ll(trainer_node* trainer_list){
	trainer_node* current = trainer_list;
	int trainer_count = 0;
	while(current != NULL){
		trainer_count++;
		current = current->next;
	}
	
	//16 nodes of ll_2d_node and trainer_count nodes of node
	ll_2d_node* head_row;
	ll_2d_node* current_row;
	slot *head_column, *current_column;
	
	int row_count = 15;
	while(row_count >= 0){
		int trainer_count_copy = trainer_count;
		if(row_count == 15){
			//creating linked list that goes in the head_row node
			head_column = create_slot_node(-1, -1, -1, -1, " ");
			current_column = head_column;
			
			time_t temp_t;
			while(trainer_count_copy > 1){
				slot* temp = create_slot_node(-1, -1, -1, -1, "");
				current_column->next = temp;
				current_column = current_column->next;
				trainer_count_copy--;
			}
			trainer_count_copy = trainer_count;
			head_row = creatnode_2d_ll(head_column);
			current_row = head_row;
			row_count--;
		}
		else{
			//creating linked list that goes in the head_row node
			head_column = create_slot_node(-1, -1, -1, -1, " ");
			current_column = head_column;
			
			time_t temp_t;
			while(trainer_count_copy > 1){
				slot* temp = create_slot_node(-1, -1, -1, -1, "");
				current_column->next = temp;
				current_column = current_column->next;
				trainer_count_copy--;
			}
			trainer_count_copy = trainer_count;
			current_row->next = creatnode_2d_ll(head_column);
			current_row = current_row->next;
			row_count--;
		}
	}
	return head_row;
}

void Print_hour_wise_list(ll_2d_node* slots_table){
	ll_2d_node* current_row = slots_table;
	slot* current_column;
	int slot_val = 6;
	
	
	while(current_row != NULL){
		printf(" \n%d \n", slot_val);
		current_column = current_row->slot_node;
		while(current_column != NULL){
			printf("member id = %d \ntrainer id = %d \ntime slot = %d \nprogram = ", current_column->member_id, current_column->trainer_id, current_column->time_slot);
			if(current_column->req_program == 1){
				printf("Yoga \n");
			}
			else if(current_column->req_program == 2){
				printf("Cardio \n");
			}
			else if(current_column->req_program == 3){
				printf("Zumba \n");
			}
			else if(current_column->req_program == 4){
				printf("weightlifting \n");
			}
			else{
				printf("no program schedules \n");
			}
			
			printf("\n");
			
			current_column = current_column->next;
		}
		printf("\n\n");
		slot_val++;
		current_row = current_row->next;
	}
}

ll_2d_node* Schedule_slot(slot* req_info, trainer_node* trainer_list, member_node* member_list, node* fee_list, int which_function){//to return either the normal output or the output required from the intersection function
																																	// 0 for the normal execution of the function and 1 for the intersection function
	//creating the kinda 2d linked list to store the schedule
	ll_2d_node* slots_table = create_schedule_ll(trainer_list);
	ll_2d_node* current_row = slots_table;
	slot* current_column;
	node *no_of_members, *no_of_members_current;// = no_of_members->next;
	
	int non_assigned = 0;	//to check if there are any non assigned members at all
	
	node* fee_list_current = fee_list;
	
	ll_2d_node* intersection_ret;	//since the return value is of this type
	slot *intersection_ret_ll = create_slot_node(-1, -1, -1, -1, " "), *intersection_ret_ll_current = create_slot_node(-1, -1, -1, -1, " ");
	intersection_ret_ll_current = intersection_ret_ll;
	
	no_of_members = createnode(0);
	no_of_members_current = no_of_members->next;
	while(current_row != NULL){
		no_of_members_current = createnode(0);
		current_row = current_row->next;
	}
	no_of_members_current = no_of_members;
	
	current_row = slots_table;
	
	member_node* non_assigned_members;
	member_node* current_non_assigned_member = non_assigned_members;
	
	slot* current_req_info = req_info;
	
	while(current_req_info != NULL){
		//checking the condn for if the trainer even takes that activity
		trainer_node* current_trainer = trainer_list;
		int error = 0;
		while(current_trainer != NULL && error == 0){
			if(current_trainer->id == current_req_info->trainer_id){
				int prog = current_req_info->req_program;
				while(prog > 0){
					if(prog == 1){	//go till you reach the required node
						if(current_trainer->programs == 0){
							error = 1;
							printf("Trainer doesn't teach this program \n");
						}
					}
					prog--;
					current_trainer->programs = current_trainer->programs->next;
				}
			}
			current_trainer = current_trainer->next;
		}
		if(error != 1){
			member_node* current_member = member_list;
			while(current_member != NULL && error == 0){
				if(current_member->id == current_req_info->member_id && current_member->booked_today == 1){
					error = 1;
					printf("Error, you can only register once per day \n");
				}
				current_member = current_member->next;
			}
		}
		
		int found = 0;
		if(error != 1 && found == 0){
			//now we'll go and insert into the block in the 2d ll
			//we have to move by (time_slot-6) towards the right and trainer_id down
			//ideal situation
			int move_right = current_req_info->time_slot - 6;
			int move_down = current_req_info->trainer_id - 1;
			
			while(move_right > 0){
				current_row = current_row->next;
				move_right--;
			}
			current_column = current_row->slot_node;
			while(move_down > 0 && current_column != NULL){
				if(current_column->member_id != -1){
					no_of_members_current->data++;
				}
				current_column = current_column->next;
				move_down--;
			}
			
			if(current_column->member_id == -1 && no_of_members_current->data<10 && found == 0){
				//copying all teh values
				current_column->member_id = current_req_info->member_id;	
				current_column->req_program = current_req_info->req_program;
				current_column->trainer_id = current_req_info->trainer_id;
				current_column->time_slot = current_req_info->time_slot;
				strcpy(current_column->timestamp , current_req_info->timestamp);
				
				intersection_ret_ll_current->member_id = current_req_info->member_id;		
				intersection_ret_ll_current->req_program = current_req_info->req_program;
				intersection_ret_ll_current->trainer_id = current_req_info->trainer_id;
				intersection_ret_ll_current->time_slot = current_req_info->time_slot;
				strcpy(intersection_ret_ll_current->timestamp , current_req_info->timestamp);
				
				no_of_members_current->data++;
				
				int fee = 0;
				member_node* current_member = member_list;
				while(current_member != NULL && found == 0){	//adding the fee based on how muchthat specific activity costs
					if(current_member->id == current_req_info->member_id && current_member->booked_today == 0){
						found = 1;
						int count = 1;
						while(fee_list_current != NULL){
							if(current_req_info->req_program == 1 && count == 1){
								current_member->fee_paid += fee_list_current->data;
								fee = fee_list_current->data;
							}
							else if(current_req_info->req_program == 2&& count == 2){
								current_member->fee_paid += fee_list_current->data;
								fee = fee_list_current->data;
							}
							else if(current_req_info->req_program == 3 && count == 3){
								current_member->fee_paid += fee_list_current->data;
								fee = fee_list_current->data;
							}
							else if(current_req_info->req_program == 4 && count == 4){
								current_member->fee_paid += fee_list_current->data;
								fee = fee_list_current->data;
							}
							fee_list_current = fee_list_current->next;
							count++;
						}
					}
					current_member = current_member->next;
				}
				
				trainer_node* current_trainer = trainer_list;
				while(current_trainer != NULL){
					if(current_req_info->trainer_id == current_trainer->id){
						current_trainer->renumeration += fee;
					}
					current_trainer = current_trainer->next;
				}
			}
			else{	//this slot has already been booked
				int status = 0;
				int no_of_times_slot_changed=0;
				
				/*
				if this is the case, then i have to use the search trainer 
				function and get the trainer list and check if any of those
				trainers are free in that slot
				=> i have to iterate through the columns and find the trainer using the trainers id
					can make it a little more efficient by checking the id of the current trainer and moving forward
					if the id if the trainer we're looking for is greater than that
					if it's lesser then we have no choice but to iterate agn
				
				if we find no slot after this too then i have to do this... go to next row and check for all these trainers agn
				*/
				int found = 0;
				while(current_row != NULL){
					current_column = current_row->slot_node;
					if(no_of_members <= 10){
						
						trainer_node* req_trainer = malloc(sizeof(trainer_node));
						node* req_program = req_trainer->programs;
						while(req_program != NULL){
							if(current_req_info->req_program == 1){
								req_program = 1;
							}
							else if(current_req_info->req_program == 2){
								req_program = 1;
							}
							else if(current_req_info->req_program == 3){
								req_program = 1;
							}
							else if(current_req_info->req_program == 4){
								req_program = 1;
							}
							else{
								req_program = 0;
							}
						}
						
						if(no_of_times_slot_changed != 0){
							//checking the no of members in the slot everytime we change the slot to make sure there aren't more than 10 ppl at the same time
							while(current_column != NULL){
								if(current_column->member_id != -1){
									no_of_members_current->data ++;
								}
							}
						}
						
						trainer_node* eligible_trainer = Search_trainer(trainer_list, req_trainer, 3);	//searching for other trainers who can fill in
						trainer_node* eligible_trainer_current = eligible_trainer;
						while(current_column != NULL && eligible_trainer_current != NULL && found == 0){
							if(current_column->trainer_id == eligible_trainer_current->id){
								if(current_column->member_id == -1){
									current_req_info->trainer_id = current_column->trainer_id;
									current_column = current_req_info;
									printf("the member %d has been assigned to trainer id = %d at the same slot \n", current_column->member_id, current_req_info->time_slot+no_of_times_slot_changed);
									found = 1;
									no_of_members_current->data ++;
									
									//adding fee and renumeration into respective records
									int found = 0;
									int fee = 0;
									member_node* current_member = member_list;
									while(current_member != NULL && found == 0){
										if(current_member->id == current_req_info->member_id && current_member->booked_today == 1){
											found = 1;
											int count = 1;
											while(fee_list_current != NULL){
												if(current_req_info->req_program == 1 && count == 1){
													current_member->fee_paid += fee_list_current->data;
													fee = fee_list_current->data;
													break;
												}
												else if(current_req_info->req_program == 2&& count == 2){
													current_member->fee_paid += fee_list_current->data;
													fee = fee_list_current->data;
													break;
												}
												else if(current_req_info->req_program == 3 && count == 3){
													current_member->fee_paid += fee_list_current->data;
													fee = fee_list_current->data;
													break;
												}
												else if(current_req_info->req_program == 4 && count == 4){
													current_member->fee_paid += fee_list_current->data;
													fee = fee_list_current->data;
													break;
												}
												fee_list_current = fee_list_current->next;
												count++;
											}
										}
										current_member = current_member->next;
									}
				
									trainer_node* current_trainer = trainer_list;
									while(current_trainer != NULL){
										if(current_req_info->trainer_id == current_trainer->id){
											current_trainer->renumeration += fee;
										}
										current_trainer = current_trainer->next;
									}
									
									no_of_members_current->data++;
								}
								current_column = current_column->next;
								eligible_trainer_current = eligible_trainer_current->next;
							}
						}
					}
					else if(no_of_members_current->data<= 10 && found == 0){
						printf("couldn't find another free trainer, checking the next free slot \n");
					}
					else if(no_of_members_current->data > 10){
						printf("10 members already registered for this slot, due to covid regulations not more than 10 members can be in the gym at the same time /n");
						printf("checking the next free slot \n");
					}
					no_of_times_slot_changed ++;
					current_row = current_row->next;
					no_of_members_current = no_of_members_current->next;
				}
				if(status == 0){		// couldn't find next slot
					non_assigned = 1;
					printf("unfortunately scheduling of slot wasn't successful due to covid norms \n");
					non_assigned_members->id = current_req_info->member_id;
					non_assigned_members = non_assigned_members->next;
				}
			}
		}
		current_row = slots_table;
		current_req_info = current_req_info->next;
	}
	if(which_function == 0){
		Print_hour_wise_list(slots_table);
		//printing the members whose scheduling wasn't possible
		current_non_assigned_member = non_assigned_members;
		while(current_non_assigned_member != NULL && non_assigned == 1){
			printf("member id = %d \n", current_non_assigned_member->id);
			current_non_assigned_member = current_non_assigned_member->next;
		}
	
		return slots_table;
	}
	else{
		intersection_ret = creatnode_2d_ll(intersection_ret_ll);
		return intersection_ret;
	}
}



member_node* Delete_member(member_node* member_list, int member_to_be_deleted_id){
	member_node* current = member_list;
	member_node* prev = member_list;
	int status = 0;
	
	
	if(member_to_be_deleted_id <1000 || member_to_be_deleted_id > 9999){
		printf("Enter valid id \n");
	}
	else{
		while(current != NULL && status == 0 && current->next != NULL){
			if(current->id == member_to_be_deleted_id){
				prev->next = current->next;
				status = 1;
				prev = prev->next;
				current = current->next;
			}
			else{
				prev = current;
				current = current->next;
			}
		}
		if(current->next == NULL && current != NULL && current->id == member_to_be_deleted_id){
			prev->next = current->next;
			status = 1;
		}
	}
	
	if(status ==0){
		printf("Enter valid id \n");
	}
	
	printf("Successfully deleted \n");
	return member_list;
}

trainer_node* Delete_trainer(trainer_node* trainer_list, int trainer_to_be_deleted_id){
	trainer_node* current = trainer_list;
	trainer_node* prev = trainer_list;
	int status = 0;
	
	while(current != NULL && status == 0){
		if(current->id == trainer_to_be_deleted_id){
			prev->next = current->next;
			status = 1;
		}
		prev = current;
		current = current->next;
	}
	if(current->next == NULL && current != NULL && current->id == trainer_to_be_deleted_id){
		prev->next = current->next;
		status = 1;
	}
	
	if(status == 0){
		printf("trainer with this id not found \n");
	}
	
	printf("Successfully deleted \n");
	return trainer_list;
}

void Search_member(member_node* member_list, member_node* member, int key_field){
	member_node* current = member_list;
	int found = 0;
	if(key_field == 1){
		while(current != NULL && found == 0){
			if(current->id == member->id){
				printf("id = %d, \nname = %s, \nage = %d, \ngender = %c, \n", current->id, current->name, current->age, current->gender);
				print_programs_enrolled(current->enrolled_programs);
				//print the fees paid as well
				found = 1;
			}
			current = current->next;
		}
	}
	else if(key_field == 2){
		while(current != NULL && found == 0){
			if(strcmp(current->name, member->name) == 0){
				printf("id = %d, \nname = %s, \nage = %d, \ngender = %c, \n", current->id, current->name, current->age, current->gender);
				print_programs_enrolled(current->enrolled_programs);
				//print the fees paid as well
				found = 1;
			}
			current = current->next;
		}
	}
	else if(key_field == 3){
		while(current != NULL && found == 0){
			if(current->age == member->age){
				printf("id = %d, \nname = %s, \nage = %d, \ngender = %c, \n", current->id, current->name, current->age, current->gender);
				print_programs_enrolled(current->enrolled_programs);
				//print the fees paid as well
				found = 1;
			}
			current = current->next;
		}
	}
	else if(key_field == 4){
		while(current != NULL /*&& found == 0*/){
			if(current->gender == member->gender){
				printf("id = %d, \nname = %s, \nage = %d, \ngender = %c, \n", current->id, current->name, current->age, current->gender);
				print_programs_enrolled(current->enrolled_programs);
				//print the fees paid as well
				found = 1;
			}
			current = current->next;
		}
	}
	else if(key_field == 5){
		while(current != NULL/* && found == 0*/){
			node* current_programs_enrolled = current->enrolled_programs;
			node* current_member = member->enrolled_programs;
			int count = 0;
			while(current_programs_enrolled != NULL  && current_member != NULL){
				if(current_programs_enrolled->data == current_member->data){
					count++;
				}
				current_programs_enrolled = current_programs_enrolled->next;
				current_member = current_member->next;
			}
			if(count == 4){
				printf("id = %d, \nname = %s, \nage = %d, \ngender = %c, \n", current->id, current->name, current->age, current->gender);
				print_programs_enrolled(current->enrolled_programs);	
				//found == 1;	
			}
			count = 0;
			current = current->next;
		}
	}
	// do we have to this for fee?
}


void Print_member_list(member_node* member_list){
	member_node* current = member_list;
	while(current != NULL){
		printf("id = %d, \nname = %s, \nage = %d, \ngender = %c, \n", current->id, current->name, current->age, current->gender);
		print_programs_enrolled(current->enrolled_programs);
		printf("\n");
		current = current->next;
	}
}

void Print_trainer_list(trainer_node* trainer_list){
	trainer_node* current = trainer_list;
	while(current != NULL){
		printf("id = %d, \nname = %s \n", current->id, current->name);
		//print_programs_enrolled(current->programs);
		printf("\n");
		current = current->next;
	}
}

trainer_node* Print_sorted_remuneration_list(trainer_node* trainer_list){
    int swapped, i;
  
    /* Checking for empty list */
    if (trainer_list == NULL){
    	printf("NULL");
	}
	else if(trainer_list->next == NULL){
		return trainer_list;
	}
    else{
    	trainer_node *sorted_trainer_list, *sorted_trainer_list_current = sorted_trainer_list, *fast = trainer_list, *slow = trainer_list;
  	  trainer_node *trainer_list_current1, *trainer_list_current2;
    
    	while(fast != NULL && fast->next != NULL){
    		fast = fast->next->next;
	    	slow = slow->next;
		}
	    trainer_list_current1 = trainer_list;
    	trainer_list_current2 = slow;
    
	    while(trainer_list_current1 != NULL && trainer_list_current2 != NULL){
    		if(trainer_list_current1->renumeration > trainer_list_current2->renumeration){
				sorted_trainer_list_current = trainer_list_current1;
			}
			else{
				sorted_trainer_list_current = trainer_list_current2;
			}
			trainer_list_current1 = trainer_list_current1->next;
			trainer_list_current2 = trainer_list_current2->next;
		}
		if(trainer_list_current1 != NULL){
			sorted_trainer_list_current = trainer_list_current1;
		}
		else if(trainer_list_current2 != NULL){
			sorted_trainer_list_current = trainer_list_current2;
		}
	
		return sorted_trainer_list;
	}
}

void Print_intersection_list(slot* req_info, trainer_node* trainer_list, member_node* member_list, node* fee_list){
	ll_2d_node* intersection_list = Schedule_slot(req_info, trainer_list, member_list, fee_list, 1);
	
	slot* intersection_list_current = intersection_list->slot_node;
	while(intersection_list_current != NULL){
		printf("\n");
		printf(" member id = %d \n trainer_id = %d \n time slot = %d \n", intersection_list_current->member_id, intersection_list_current->trainer_id, intersection_list_current->time_slot);
		if(intersection_list_current->req_program == 1){
			printf("Yoga \n");
		}
		else if(intersection_list_current->req_program == 2){
			printf("Cardio \n");
		}
		else if(intersection_list_current->req_program == 3){
			printf("Zumba \n");
		}
		else if(intersection_list_current->req_program == 4){
			printf("weightlifting \n");
		}
		else{
			printf("no program schedules \n");
		}
		intersection_list_current = intersection_list_current->next;
	}
}

int rand_interval(int min, int max, member_node* member_list){
	int r, ret_val = 0;
	const int range = 1+ max - min;
	const int buckets = RAND_MAX/range;
	const int limit = buckets*range;
	
	do{
		r = rand();
	}while(r >= limit);
	
	
	member_node* current_member = member_list;
	while(ret_val == 0){
		while(current_member != NULL && ret_val == 0){
			if(current_member->id != (min+(r / buckets))){
				ret_val = min+(r / buckets);	//making sure the id doesn't already exist
			}
		}
		if(ret_val == 0){
			do{
				r = rand();
			}while(r >= limit);
			
		}
	}
	return ret_val;
}

int main(){
	int entered_val = 0;
	node* dummy_program = createnode(-1);
	member_node* member_list = create_member(-1, " ", -1, '$', -1, dummy_program, -1);
	
	trainer_node* trainer_list = create_trainer(-1, " ", dummy_program, -1);
	
	ll_2d_node* slots_table = create_schedule_ll(trainer_list);
	
	slot* req_info_dummy = create_slot_node(-1, -1, -1, -1, "");
	slot* req_info_head = req_info_dummy->next;
	
	printf("Enter the price to be paid and recieved for each program \n");
	node *fee_list, *fee_list_current;
	for(int i = 0; i<4; i++){
		int fee = 0;
		//scanf("%d", &prog);
		if(i == 0){
			printf("Enter price for Yoga \n");
			scanf("%d", &fee);
			fee_list = createnode(fee);
			fee_list_current = fee_list->next;
		}
		else if(i == 1){
			printf("Enter price for Cardio \n");
			scanf("%d", &fee);
			node* temp = createnode(fee);
			fee_list_current = temp;
			fee_list_current = fee_list_current->next;
		}
		else if(i == 2){
			printf("Enter price for Zumba \n");
			scanf("%d", &fee);
			node* temp = createnode(fee);
			fee_list_current = temp;
			fee_list_current = fee_list_current->next;
		}
		else if(i == 3){
			printf("Enter price for Weight Lifting \n");
			scanf("%d", &fee);
			node* temp = createnode(fee);
			fee_list_current = temp;
			fee_list_current = fee_list_current->next;
		}
	}
	
	printf("Enter 1 to add member \n");
	printf("Enter 2 to add trainer \n");
	printf("Enter 3 to delete member \n");
	printf("Enter 4 to delete trainer \n");
	printf("Enter 5 to search member \n");
	printf("Enter 6 to search trainer \n");
	printf("Enter 7 to print member list \n");
	printf("Enter 8 to print trainer list \n");
	printf("Enter 9 to schedule slot \n");
	printf("Enter 10 to print hour wise list \n");
	printf("Enter 11 to print sorted renumeration list oftrainers \n");
	printf("Enter 12 to print the numbers that have been assigned to their preferred trainers \n");
	printf("Enter 13 to exit \n");
	
	do{
		printf("Enter choice \n");
		scanf("%d", &entered_val);
		
		
		
		switch(entered_val){
			case 1:{
				char member_name[50];
				char gender;
				int age = 0;
				
				printf("Enter name, gender and age of the member \n");
				scanf("%s\n %c \n %d", &member_name, &gender, &age);
				
				printf("enter the preferred programs \n");
				
				node *program, *programs_current;
				for(int i=0; i<4; i++){
					int prog = 0;
					printf("enter 0 if member doesn't take this activity and 1 otherwise \n");
					if(i == 0){
						printf("Yoga : \n");
					}
					else if(i == 1){
						printf("Cardio : \n");
					}
					else if(i == 2){
						printf("Zumba : \n");
					}
					else if(i == 3){
						printf("Weight Lifting : \n");
					}
					scanf("%d", &prog);
					if(i == 0){
						program = createnode(prog);
						programs_current = program;
					}
					else{
						//node* temp = createnode(prog);
						programs_current->next = createnode(prog);
						programs_current = programs_current->next;
					}
				}
				programs_current = program;
				while(programs_current != NULL){
					printf("%d ", programs_current->data);
					programs_current = programs_current->next;
				}
				int id = rand_interval(1000, 10000, member_list);
				member_node* new_member = create_member(id, member_name, age, gender, 0, program, 0);
				member_list = Add_member(member_list, new_member);
				break;
			}
			case 2:{
				char trainer_name[50];
				int id = 0;
				
				printf("Enter name, id of the trainer \n");
				scanf("%s\n %d", &trainer_name, &id);
				
				printf("enter the preferred programs \n");
				node *program, *programs_current;
				for(int i=0; i<4; i++){
					int prog = 0;
					printf("enter 0 if trainer doesn't take this activity and 1 otherwise \n");
					if(i == 0){
						printf("Yoga : ");
					}
					else if(i == 1){
						printf("Cardio : ");
					}
					else if(i == 2){
						printf("Zumba : ");
					}
					else if(i == 3){
						printf("Weight Lifting : ");
					}
					scanf("%d", &prog);
					if(i == 0){
						program = createnode(prog);
						programs_current = program;
					}
					else{
						programs_current->next = createnode(prog);
						programs_current = programs_current->next;
					}
				}
				trainer_node* new_trainer = create_trainer(id, trainer_name, program, 0);
				trainer_list = Add_trainer(trainer_list, new_trainer);
				break;
			}
			case 3:{
				printf("Enter the id of the member to be deleted \n");
				int member_id;
				scanf("%d", &member_id);
				member_list = Delete_member(member_list, member_id);
				break;
			}
			case 4:{
				printf("Enter the id of teh trainer to be deleted \n");
				int trainer_id;
				scanf("%d", &trainer_id);
				trainer_list = Delete_trainer(trainer_list, trainer_id);
				break;
			}
			case 5:{
				printf("enter key field to search for member \n");
				printf(" enter 1 to search by id \n enter 2 to search by name \n enter 3 to search by age \n enter 4 to search by gender \n enter 5 to search by program \n");
				int key_field = 0;
				scanf("%d", &key_field);
				
				if(key_field == 1){
					int id;
					printf("Enter the id of the member to be searched for \n");
					scanf("%d", &id);
					node* dummy_program = createnode(-1);
					member_node* search_member_field = create_member(id, " ", -1, '$', -1, dummy_program, -1);
					Search_member(member_list, search_member_field, key_field);
				}
				else if(key_field == 2){
					char name[50];
					printf("Enter name of the member to be searched for \n");
					scanf("%s", &name);
					node* dummy_program = createnode(-1);
					member_node* search_member_field = create_member(-1, name, -1, '$', -1, dummy_program, -1);
					Search_member(member_list, search_member_field, key_field);
				}
				else if(key_field == 3){
					int age;
					printf("Enter age of the member to be searched for \n");
					scanf("%d", &age);
					node* dummy_program = createnode(-1);
					member_node* search_member_field = create_member(-1, " ", age, '$', -1, dummy_program, -1);
					Search_member(member_list, search_member_field, key_field);
				}
				else if(key_field == 4){
					char gender;
					printf("Enter gender of the member to be searched for \n");
					fflush(stdin);
					scanf("%c", &gender);
					printf("* gender = %c *\n", gender);
					node* dummy_program = createnode(-1);
					member_node* search_member_field = create_member(-1, " ", -1, gender, -1, dummy_program, -1);
					Search_member(member_list, search_member_field, key_field);
				}
				else if(key_field == 5){
					node *programs, *programs_current;
					for(int i=0; i<4; i++){
						int prog = 0;
						printf("enter 0 if member doesn't take this activity and 1 otherwise \n");
						if(i == 0){
							printf("Yoga : ");
						}
						else if(i == 1){
							printf("Cardio : ");
						}
						else if(i == 2){
							printf("Zumba : ");
						}
						else if(i == 3){
							printf("Weight Lifting : ");
						}
						scanf("%d", &prog);
						if(i == 0){
							programs = createnode(prog);
							programs_current = programs;
						}
						else{
							programs_current->next = createnode(prog);
							programs_current = programs_current->next;
						}
					}
					member_node* search_member_field = create_member(-1, " ", -1, '$', -1, programs, -1);
					Search_member(member_list, search_member_field, key_field);
				}
				else{
					printf("Enter valid key field \n");
				}
				break;
			}
			case 6:{
				//int Id, char Name[], node* Program, int Renumeration
				printf("enter key field to search for trainer \n");
				printf(" enter 1 to search by id \n enter 2 to search by name \n enter 3 to search by program \n");
				int key_field = 0;
				scanf("%d", &key_field);
				
				if(key_field == 1){
					int id;
					printf("Enter the id of the member to be searched for \n");
					scanf("%d", &id);
					node* dummy_program = createnode(-1);
					trainer_node* search_trainer_field = create_trainer(id, " ", dummy_program, -1);
					Search_trainer(trainer_list, search_trainer_field, key_field);
				}
				else if(key_field == 2){
					char name[50];
					printf("Enter name of the member to be searched for \n");
					scanf("%s", &name);
					node* dummy_program = createnode(-1);
					trainer_node* search_trainer_field = create_trainer(-1, name, dummy_program, -1);
					Search_trainer(trainer_list, search_trainer_field, key_field);
				}
				else if(key_field == 3){
					node *programs, *programs_current;
					for(int i=0; i<4; i++){
						int prog = 0;
						printf("enter 0 if trainer doesn't take this activity and 1 otherwise \n");
						if(i == 0){
							printf("Yoga : ");
						}
						else if(i == 1){
							printf("Cardio : ");
						}
						else if(i == 2){
							printf("Zumba : ");
						}
						else if(i == 3){
							printf("Weight Lifting : ");
						}
						scanf("%d", &prog);
						if(i == 0){
							programs = createnode(prog);
							programs_current = programs;
						}
						else{
							programs_current->next = createnode(prog);
							programs_current = programs_current->next;
						}
					}
					trainer_node* search_trainer_field = create_trainer(-1, " ", programs, -1);
					Search_trainer(trainer_list, search_trainer_field, key_field);
				}
				else{
					printf("Enter valid key field \n");
				}
				break;
			}
			case 7:{
				Print_member_list(member_list);
				break;
			}
			case 8:{
				Print_trainer_list(trainer_list);
				break;
			}
			case 9:{
				int member_id = 0, trainer_id = 0, time_slot = 0, program_requested_int = 0;
				char time_stamp[70];
				node *programs_requested, *programs_requested_current;
				printf("Enter the req information to book a slot \n");
				printf("Enter member id, trainer id, time slot \n");
				scanf("%d\n %d\n %d", &member_id, &trainer_id, &time_slot);
				printf("Enter 1 if you want to take Yoga \n");
				printf("Enter 2 if you want to take Cardio \n");
				printf("Enter 3 if you want to take Zumba \n");
				printf("Enter 4 if you want to take Weight Lifting \n");
				scanf("%d", &program_requested_int);
				
				for(int i = 0; i<4; i++){
					if(i == program_requested_int-1 && i == 0){
						programs_requested = createnode(1);
						programs_requested_current = programs_requested;
					}
					else if(i == program_requested_int-1 && i == 1){
						programs_requested_current->next = createnode(0);
							programs_requested_current = programs_requested_current->next;
					}
					else if(i == program_requested_int-1 && i == 2){
						programs_requested_current->next = createnode(0);
						programs_requested_current = programs_requested_current->next;
					}
					else if(i == program_requested_int-1 && i == 3){
						programs_requested_current->next = createnode(0);
						programs_requested_current = programs_requested_current->next;
					}
					else{
						if(i == 0){
							programs_requested = createnode(0);
							programs_requested_current = programs_requested;
						}
						else{
							programs_requested_current->next = createnode(0);
							programs_requested_current = programs_requested_current->next;
						}
					}
				}
				
				struct tm* ptr;
    			time_t t;
				t = time(NULL);
    			ptr = localtime(&t);
    			strcpy(time_stamp, asctime(ptr));
    			
//				temp->req_program = Req_program;
//				strcpy(temp->timestamp , Timestamp);
				
				req_info_head = create_slot_node(member_id, trainer_id, time_slot, program_requested_int, time_stamp);
				ll_2d_node* slots_table = Schedule_slot(req_info_head, trainer_list, member_list, fee_list, 0);
				break;
			}
			case 10:{
				Print_hour_wise_list(slots_table);
				break;
			}
			case 11:{
				trainer_node* trainer_renumeration_list = Print_sorted_remuneration_list(trainer_list);
				Print_trainer_list(trainer_renumeration_list);
				break;
			}
			case 12:{
				Print_intersection_list(req_info_head, trainer_list, member_list, fee_list);
				break;
			}
			case 13:{
				printf("EXIT \n");
				break;
			}
			default:{
				printf("invalid choice \n");
				//break;
			}
		}
	}while(entered_val!=13);// && entered_val>0);
	
	struct tm* ptr;
	time_t t;
	t = time(NULL);
	ptr = localtime(&t);
	if(ptr->tm_hour == 23 && ptr->tm_min == 59){
		printf("its 12 \n");
		member_node* current = member_list;
		while(current != NULL){
			current->booked_today = 0;
			current = current->next;
		}
	}
	
	return 0;
}
