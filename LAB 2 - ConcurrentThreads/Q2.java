import java.io.*; 
import java.util.*; 

// implementing threads by subclassing from Thread class


class yukti2{
	public static void main(String[] args) {		
		int initialCap = generate(1, 15);
		System.out.println("The Initial capacity of Array is = "+initialCap);
		UnboundedArray array = new UnboundedArray(initialCap);
		for(int i=0;i<10;i++){
       		array.insert(generate(1,100));
        }
        array.display();		
		// creating instances of all threads			
		InsertThread insertThread = new InsertThread("Insert_Thread", array);		
		DeleteSingleThread deleteSingleThread = new DeleteSingleThread("DeleteSingle_Thread", array);
		DeleteRangeThread deleteRangeThread = new DeleteRangeThread("DeleteRange_Thread", array);
		ModifyThread modifyThread = new ModifyThread("Modify_Thread",array);
		
		// starting all threads
		insertThread.start();
		deleteSingleThread.start();
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
		while(true) {
			for(int i = 1; i<= 3; i++) {
				int element = generate(1, 100);
				array.insert(element);
			}
			
			try {
				sleep(5000); // sleep for 1 sec
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
	// overriding run() method of thread class
	public void run() {
		while(true) {
			for(int i = 1; i<= 2; i++) {
				int idx = generate(0,array.getSize()-1);
				array.delete(idx);
			}
			
			try {
				sleep(5000); 
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
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
	// overriding run() method of thread class
	public void run() {
		while(true) {
			int s = array.getSize();
			int l = s/4;
			int h = l*3;
			array.delete(l,h);			
			try {
				sleep(5000); 
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
	// overriding run() method of thread class
	public void run() {
		while(true) {
			
			int x = generate(0,array.getSize()-1);
			System.out.println("Index = "+x);
			int y = generate(0,100);
			array.modify(x,y);	
			
			try {
				sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}


// JAVA PROGRAM FOR DYNAMIC ARRAY
class UnboundedArray{
    
    private int[] array;     
    private int size;   
    private int capacity;   
    
    // constructor of Dynamic array class
    public UnboundedArray(int initialCapacity){
        capacity = initialCapacity;
        array = new int[initialCapacity];
        size = 0;        
    }     
    public int getSize(){
    	return size;
    }
    public void resize(){
    	// if elements are more than 75%
    	if(size >= (capacity*0.75)){
    		    System.out.println("\nIncreasing the array size "+capacity+" to "+ capacity*2);
                capacity = capacity*2;
                int[] newarr = new int[capacity];
                for(int i=0;i<size;i++){
                    newarr[i] = array[i];
                }
                array = newarr;                
         }
         // if elements are less than 25%
         if(size <= capacity*0.25){     
         		if (capacity/2 <= 4)
         			return ;       
				System.out.println("\nDecreasing the array size "+capacity+" to "+ capacity/2);
				capacity = capacity/2;
				int[] newarr = new int[capacity];		    
				for(int i=0;i<size;i++){
				    newarr[i] = array[i];
				}
				array = newarr;          
        }  
    
    }   
    // inserts given item at the end 
    public void insert(int item){         
        if(size == capacity){
            System.out.print("Sorry!The Array is full ");  
            resize();
            return ;      
        }
        else{
            System.out.println("Inserting element - "+item);
            array[size++] = item;   
            resize();  
            display(); 
            //return ;       
    	}    
    }  
    // deletes first item of array   
    public void delete(){        
        if(size == 0){
            System.out.println("Sorry! Array Underflow..");
            resize();
            return;
        }        
        for(int i=0;i<size-1;i++){
            array[i] = array[i+1];
        }
        size--;
        System.out.println("Deleted element - "+array[0]);   
        resize();
        display();
        return ;         
        
    }
    // deletes item at particular index
    public void delete(int index){        
       if(size == 0){
            System.out.println("Sorry! Array Underflow..");
            resize();
            return;
        }
        System.out.println("Deleting element - "+array[index]);           
        for(int i=index;i<size-1;i++){            
        	array[i] = array[i+1];        
    	}
        size--;
        resize();
        display();    
        return ;            
        
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
    // to modify an element at a particular index
    public void modify(int index,int newElement){  
    	if (size == 0){
    		System.out.println("No elements to modify in the array!");
    		return ;
    	}    
    	else if (index < 0 || index > size){
    		//System.out.println("Sorry! Given index is invalid...");
    		System.out.println("The Element at 0 modified to - "+newElement);      
    		array[0] = newElement; 
    		return ;
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


