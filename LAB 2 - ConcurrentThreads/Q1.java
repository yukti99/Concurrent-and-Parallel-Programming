import java.lang.*;
import java.util.*;

class DynamicArray{
    
    private int[] array;
    private int size;
    private int capacity;
    
    public DynamicArray(int initialCapacity){
        capacity = initialCapacity;
        array = new int[initialCapacity];
        size = 0;        
    }     
    public void resize(){
    	if(size >= (capacity*0.75)){
    		    System.out.println("Resizing the array from "+capacity+" to "+ capacity*2);
                capacity = capacity*2;
                int[] newarr = new int[capacity];
                for(int i=0;i<size;i++){
                    newarr[i] = array[i];
                }
                array = newarr;
                
         }
         if(size <= capacity*0.25){            
		    System.out.println("Resizing the array from "+capacity+" to "+ capacity/2);
		    capacity = capacity/2;
		    int[] newarr =new int[capacity];		    
		    for(int i=0;i<size;i++){
		        newarr[i] = array[i];
		    }
		    array = newarr;            
        }   
    
    }    
    public void insert(int item){         
        if(size == capacity){
            System.out.print("Error: Array is full ");        
        }
        else{
            System.out.println("Inserting element - "+item);
            array[size++] = item;   
            resize();  
            display();
        
    	}
    
    }
     
    public void delete(){        
        if(size == 0){
            System.out.print("Sorry! Array Underflow..");
            return;
        }          
        for(int i=0;i<size-1;i++){
            array[i] = array[i+1];
        }
        size--;
        System.out.println("Deleted element - "+array[0]);   
        resize();
        display();      
        
    }
     
    public void delete(int index){        
        if(size == 0){
            System.out.print("Sorry! Array Underflow..");
            return;
        }
        System.out.println("Deleting element - "+array[index]);           
        for(int i=index;i<size-1;i++){            
        	array[i] = array[i+1];        
    	}
        size--;
        resize();
        display();             
        
    }
    // function to delete all elements for startindex to endindex
    public void delete(int startIndex,int endIndex){        
        if(endIndex > size||startIndex > endIndex ||startIndex < 0){
            System.out.println("Sorry! Given index is invalid...");
            return;
        }
        System.out.println("Deleting elements in range "+startIndex+" to "+endIndex);     
        int s = startIndex;
        for(int i = endIndex+1;i<size;i++){
           array[s++] = array[i];
        }
        size = size-(endIndex-startIndex+1);  
        resize();
        display();
            
    }
    public void modify(int index,int newElement){  
    	if (size == 0){
    		System.out.println("No elements to modify in the array!");
    		return ;
    	}      
        else if(index < 0 || index > size){
            System.out.println("Sorry! Given index is invalid...");
            return;
        }  
        System.out.println("The Element at "+index+" modified to - "+newElement);      
        array[index] = newElement;        
    }    
    public void display(){
        System.out.println("\nDynamic Array : ");
        for(int i=0;i<size;i++){
            System.out.print(array[i]+ " ");
        }
        System.out.println();
    }     
}

class yukti1{
    public static int generateNo(int min, int max) {
    	return min + (int)(Math.random() * ((max - min) + 1));
    }   
    
    public static void main(String[] args) {        
       DynamicArray da = new DynamicArray(10);
       for(int i=0;i<10;i++){
       		da.insert(generateNo(1,100));
       }
       da.display();
       System.out.println("Deleting the elements from index 4 to 7");
       da.delete(4, 7);
       da.display();
       System.out.println("Modifying the element at index 1");
       da.modify(1,5);
       da.display();
       System.out.println("Deleting 1st element of array");
       da.delete();       
       System.out.println("Deleting the element at given index - 2");
       da.delete(2);       
       
        
    }
    
}
