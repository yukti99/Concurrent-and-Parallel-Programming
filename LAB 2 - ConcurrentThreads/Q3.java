import java.util.*;

class yukti3{
	public static void main(String[] args) {		
		int initialCapacity = generate(1, 10);
		System.out.println("The Initial capacity is = "+initialCapacity);
		UnboundedArray array = new UnboundedArray(initialCapacity);	
		for(int i=0;i<10;i++){
       		array.insert(generate(1,100));
        }
        array.printArray();			
		InsertThread insertThread = new InsertThread("Insert_Thread", array);		
		DeleteSingleThread deleteSingleThread = new DeleteSingleThread("DeleteSingle_Thread", array);
		DeleteRangeThread deleteRangeThread = new DeleteRangeThread("DeleteRange_Thread", array);
		ModifyThread modifyThread = new ModifyThread("Modify_Thread",array);
		
		insertThread.start();
		deleteSingleThread.start();
		insertThread.start();
		deleteRangeThread.start();
		modifyThread.start();
	}
	public static int generate(int min, int max) {
		return min + (int) (Math.random() * ((max - min) + 1));
	}
}
class InsertThread extends Thread {
	private UnboundedArray array;
	public InsertThread(String name, UnboundedArray array) {
		
		super(name);
		this.array = array;
	}
	public static int generate(int min, int max) {
		return min + (int) (Math.random() * ((max - min) + 1));
	}

	public void run() {
			for(int i = 1; i<= 3; i++) {
				int element = generate(1, 100);
				array.insert(element);
		
			
			try {
				sleep(1000); // 5 sec sleep
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
class DeleteSingleThread extends Thread{
	private UnboundedArray array;
	public DeleteSingleThread(String name, UnboundedArray array) {		
		super(name);
		this.array = array;
	}
	public static int generate(int min, int max) {
		return min + (int) (Math.random() * ((max - min) + 1));
	}
	public void run() {
		while(true) {
			for(int i = 1; i<= 2; i++) {
			// generates the index
				int x = generate(0,array.getSize()-1);
				array.delete(x);
			}
			
			try {
				sleep(1000); // 5 sec sleep
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
class ModifyThread extends Thread{
	private UnboundedArray array;
	public ModifyThread(String name, UnboundedArray array) {		
		super(name);
		this.array = array;
	}
	public static int generate(int min, int max) {
		return min + (int) (Math.random() * ((max - min) + 1));
	}
	public void run() {
			int x = generate(0,array.getSize()-1);
			System.out.println("x = "+x);
			int y = generate(0,100);
			array.modify(x,y);	
			
			try {
				sleep(1000); // 5 sec sleep
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

class DeleteRangeThread extends Thread{
	private UnboundedArray array;
	public DeleteRangeThread(String name, UnboundedArray array) {		
		super(name);
		this.array = array;
	}
	public static int generate(int min, int max) {
		return min + (int) (Math.random() * ((max - min) + 1));
	}
	public void run() {
			int s = array.getSize();
			array.delete(s/4,(s*3)/4);			
			try {
				sleep(1000); // 5 sec sleep
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
}


class UnboundedArray{
    
    private int[] array;
    private int size;
    private int capacity;
    
    public UnboundedArray (int initialCapacity){
        capacity = initialCapacity;
        array = new int[initialCapacity];
        size = 0;        
    } 
    public int getSize(){
    	return size;
    } 
    
    public void adjust(){
    	if(size >= (capacity*0.75)){
    		System.out.println("\nResizing the array from "+capacity+" to "+ capacity*2);
                capacity = capacity*2;
                int[] newArray = new int[capacity];
                for(int i=0;i<size;i++){
                    newArray[i] = array[i];
                }
                array = newArray;
                
         }else if(size <= capacity*0.25){    
         	    if (capacity/2 ==  0)
         	    	return ;        
		    System.out.println("\nResizing the array from "+capacity+" to "+ capacity/2);
		    capacity = capacity/2;
		    int[] newArray =new int[capacity];		    
		    for(int i=0;i<size;i++){
		        newArray[i] = array[i];
		    }
		    array = newArray;            
        }
    
    
    }    
    public void insert(int element){ 
        
        if(size == capacity){
            System.out.print("Error: Array is full ");            
            
        }else{
            System.out.println("Inserting element - "+element);
            if (size<0)
            	size=0;
            array[size++] = element;   
            adjust();  
            printArray();        
        
    	}
    
    }
    // deletes 1st element 
    public void delete(){        
        if(size == 0){
            System.out.print("Error : array Underflow ! ");
            return;
        }     
        System.out.println("Deleting element - "+array[0]);   
        for(int i=0;i<size-1;i++){
            array[i] = array[i+1];
        }
       // array[size-1]=0;
        size--;
        adjust(); 
        printArray();      
        
    }
    
    // deleted at index    
    public void delete(int index){        
        if(size == 0){
            System.out.print("Error : array Underflow ! ");
            return;
        }
        System.out.println("Deleting element - "+array[index]);           
        for(int i=index;i<size-1;i++){            
        	array[i] = array[i+1];
        
    	}
        //array[size-1]=0;
        size--;
        adjust();
        printArray();
        
        
    }
    // deletes within a range
    public void delete(int startIndex,int endIndex){ 
    	if(size == 0){
            System.out.print("Error : array Underflow ! ");
            return;
        }       
        if(endIndex > size||startIndex > endIndex ||startIndex < 0){
            System.out.println("Error: Invalid index ");
            return;
        }
        System.out.println("Deleting elements in range "+startIndex+" and "+endIndex);     
        int w = startIndex;
        for(int i = endIndex+1;i<size;i++){
           array[w++] = array[i];
        }
        size = size-(endIndex-startIndex+1);  
        adjust();
        printArray();  
            
    }
    public void modify(int index,int newElement){  
    	if (size == 0){
    		System.out.println("No elements to modify in the array!");
    		return ;
    	}      
        if(index < 0 || index > size){
            System.out.println("Error: Index does not exist ");
            return;
        }  
        System.out.println("The Element at "+index+" modified to - "+newElement);      
        array[index] = newElement;        
    }    
    public void printArray(){
        System.out.println("\nThe array is as follows : ");
        for(int i=0;i<size;i++){
            System.out.print(array[i]+ " ");
        }
        System.out.println();
    } 
    
}


