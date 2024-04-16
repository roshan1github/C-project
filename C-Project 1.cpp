#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

// Define a structure to store student information
struct information {
    char name[20];
    char email[30];
    char faculty[20];
    int roll;
};


// Declare an array of structures to store student records and a variable to keep track of the number of records
struct information student[100];
int std_records=0;

// Function to load student information from a file
void load_information(int*std_records) {
    FILE *file=fopen("database.txt","r");
    if (file==NULL) {
        printf("Unable to open file.\n");
        return;
    }

    // Read data from the file and populate the student array
    while (fscanf(file," %s %s %d %s",&student[*std_records].name,&student[*std_records].email,&student[*std_records].roll,&student[*std_records].faculty)==4) {
        (*std_records)++;
        if (*std_records>=100) {
            printf("Record full.\n");
            break;
        }
    }

    fclose(file); // Close the file
}

// Function to save student information to a file
void save_information(int*std_records) {
    FILE *file=fopen("database.txt","w");
    if(file==NULL) {
        printf("Unable to open file for writing.\n");
        return;
    }

    // Write data from the student array to the file
    for (int i=0;i<*std_records;i++) {
        fprintf(file,"%s %s %d %s\n",student[i].name,student[i].email,student[i].roll,student[i].faculty);
    }

    fclose(file); // Close the file
}

// Function to add a new student record
void add_record(struct information new_student) {
    if (std_records>=100) {
        printf("Records is full.\n");
        return;
    }
    // Copy data from the new student to the student array
    for (int i=0;i<20-1 && new_student.name[i]!=EOF;i++) {
        student[std_records].name[i]=new_student.name[i];
    }
    student[std_records].name[20-1]=EOF;
    for (int i=0;i<30-1 && new_student.email[i]!=EOF;i++) {
        student[std_records].email[i]=new_student.email[i];
    }
    student[std_records].email[30-1]=EOF;
    student[std_records].roll=new_student.roll;
    for (int i=0;i<20-1 && new_student.faculty[i]!=EOF;i++) {
        student[std_records].faculty[i] = new_student.faculty[i];
    }
    student[std_records].faculty[20-1]=EOF;
    std_records++;
    printf("Record added successfully.\n");
    save_information(&std_records); // Save updated records to file
}

// Function to display all student records
void display_records() {
    if (std_records==0) {
        printf("Record is empty.\n");
        return;
    }
    printf("Records in the information:\n");
    for (int i=0;i<std_records;i++) {
        printf("Name:%s,Email:%s,Roll:%d,Faculty:%s\n",student[i].name,student[i].email,student[i].roll,student[i].faculty);
    }
}

// Main function
int main() {
    load_information(&std_records); // Load existing records from file

    int choice;

    // Menu loop
    while(1) {
        printf("\nStudent Information Management system\n");
        printf("1.Add record\n");
        printf("2.Display records\n");
        printf("3.Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch (choice) {
            case 1: {
                struct information new_student;
                printf("Enter name: ");
                fflush(stdin);
                gets(new_student.name);
                printf("Enter email: ");
                scanf("%s",&new_student.email);
                printf("Enter roll: ");
                scanf("%d",&new_student.roll);
                printf("Enter faculty: ");
                fflush(stdin);
                gets(new_student.faculty);
                add_record(new_student); // Add a new record
                break;
            }
            case 2:
                display_records(); // Display all records
                break;
            case 3:
                printf("Exiting program.\n");
                exit(0); // Exit the program
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

