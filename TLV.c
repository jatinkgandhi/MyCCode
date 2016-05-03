#include <stdio.h>
#include <string.h>

/* TLV is tag, length value Targeted with arduino platform */
#define MAX_MEMORY_SIZE	(200)
/* First byte will indicate first boot.., rest will be given to TLV manager*/
/* Memory represents here the EEPROM */
unsigned char memory[MAX_MEMORY_SIZE];
/* FIXME: multiple tags not supported */
/* ___________________________
 *|   Tag   | length |  Value |
 *|_________|________|________|
 *
 */

unsigned char scratchpad[255];

unsigned char *eeprom;

typedef enum _tags
{
	TAG_BOOTUP_TEXT = 0x81, /* Non printable ASCII character */
	TAG_USER_NAME,
	MENU_TEXT_1,
	MENU_TEXT_2
}tags;
/* Tag interpretation compeltely depends on the application */
unsigned char ItIsFirstBoot()
{
		/* Read memory first byte */
		return (0 == memory[0]) ? 1 : 0;
}
void FirstBootDone()
{
	memory[0] = 0xD0; /* Write to memory that subsequent is no longer first boot */
}

unsigned short find_empty_slot(void)
{
	unsigned short index;
	unsigned char  found_empty_space;
	
	found_empty_space = 0;
	
	/* Why continue if empty space is found ;-) */
	for(index = 0; (index < MAX_MEMORY_SIZE) && (0 == found_empty_space); index++)
	{
		switch(eeprom[index])
		{
			case TAG_BOOTUP_TEXT:
			case TAG_USER_NAME:
			case MENU_TEXT_1:
			case MENU_TEXT_2:
			{
				/*  Add length of the tag element which is next byte + storage for length byte (1) itself */
				index += eeprom[(index+1)];
				index += 2;
			}break;
			default:
			{
				found_empty_space = 1;
			}break;
		}
		if(1 == found_empty_space) break;
	}

	if(1 == found_empty_space) {  return index; } else { return 0xFFFF; }
}

unsigned short findTag(tags tag)
{
	unsigned short index_of_tag;
	
	if(tag < TAG_BOOTUP_TEXT || tag > MENU_TEXT_2) return 0xFFFF;

	for(index_of_tag = 0; index_of_tag < MAX_MEMORY_SIZE; index_of_tag++)
	{
		if(tag == eeprom[index_of_tag]) { break; }
	}
	if(index_of_tag >= MAX_MEMORY_SIZE) index_of_tag = 0xFFFF;
	
	return index_of_tag;
}

void setValueAtTag(tags tag, unsigned char *value,unsigned char length)
{
	unsigned short mem_location_of_tag;
	unsigned char  dataptr = 0;
	/*Case 1: tag element don't exist in eeprom */
	mem_location_of_tag = findTag(tag);
	if(0xFFFF == mem_location_of_tag)
	{
			mem_location_of_tag = find_empty_slot();
			if(0xFFFF == mem_location_of_tag) { printf("No space left\n"); return; }
			/* Else */
			eeprom[mem_location_of_tag] = tag;
			eeprom[mem_location_of_tag+1] = length;
			
			for(dataptr = 0; dataptr < length; dataptr++)
				eeprom[mem_location_of_tag+ 2 + dataptr] = value[dataptr];
	}
	/* Case 2: tag element exists inn eeprom */
	else
	{
		/* Stored length less than the requested length */
		if(length > eeprom[mem_location_of_tag +1])
			length =  eeprom[mem_location_of_tag+1]; /* Trim to maximum value */
		/* To enable more data than actaully stored, as at the end of data, 
		there might be value of another  tag element, we need to shift everything 
		down in the eeprom.. not implemented yet..., hence trimming down
	    Stored length greater than requested length than trim down 
        portion of data (can throw error if we want to)*/
		for(dataptr = 0; dataptr < length; dataptr++)
			eeprom[mem_location_of_tag + 2 + dataptr] = value[dataptr];
	}
}

unsigned char * getValuesAtTag(tags tag)
{
	unsigned short mem_location_of_tag;
	unsigned char  length, dataptr = 0;
	mem_location_of_tag = findTag(tag);
	if(0xFFFF != mem_location_of_tag)
	{
		memset(scratchpad,0,255);
		length = eeprom[mem_location_of_tag+1];
		for(dataptr = 0; dataptr < length; dataptr++)
			scratchpad[dataptr] = eeprom[mem_location_of_tag + 2 + dataptr];

		return &(scratchpad[0]);
	}else
	{
		return NULL;
	}
}
/* debug code */
void dumpeeprom()
{
	unsigned short index;
	printf("\n=================================\n");	
	for(index = 0; index < MAX_MEMORY_SIZE; index++)
		printf("0x%02x, ",memory[index]);
	printf("\n");
}

/* Test Code */
int main(int argc, char **argv)
{
	unsigned char *data;
	unsigned char data_buff[4];
	eeprom = &(memory[1]);
	
	if(ItIsFirstBoot()) FirstBootDone();
	dumpeeprom();
	setValueAtTag(TAG_BOOTUP_TEXT,"Hi All this is msg box\0",23);
	dumpeeprom();
	/* Don't support direct value, Should be readable lvalues */
	
	data_buff[0]  = 0xDE; data_buff[1]  = 0xAD; data_buff[2]  = 0xBA; data_buff[3]  = 0x11;
	
	setValueAtTag(TAG_USER_NAME,data_buff,4);	dumpeeprom();
	setValueAtTag(MENU_TEXT_1,"Switch ON\0",10); setValueAtTag(MENU_TEXT_2,"Switch OFF\0",11);
	dumpeeprom();
	data = getValuesAtTag(TAG_BOOTUP_TEXT);
	if(NULL != data) printf("TAG_BOOTUP_TEXT: %s\n",data);

	data = getValuesAtTag(TAG_USER_NAME);
	if(NULL != data) printf("0x%02x%02x%02x%02x\n",data[0],data[1],data[2],data[3]);
	
	data_buff[0]  = 0xBA; data_buff[1]  = 0xDC; data_buff[2]  = 0x0D; data_buff[3]  = 0xE0;
	
	setValueAtTag(TAG_USER_NAME,data_buff,4);
	dumpeeprom();
	data = getValuesAtTag(MENU_TEXT_1);
	if(NULL != data) printf("MENU_TEXT_1: %s\n",data);
	data = getValuesAtTag(MENU_TEXT_2);
	if(NULL != data) printf("MENU_TEXT_2: %s\n",data);
	data = getValuesAtTag(TAG_USER_NAME);
	if(NULL != data) printf("0x%02x%02x%02x%02x\n",data[0],data[1],data[2],data[3]);
	return 0;
}
