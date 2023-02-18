```java
public enum OS {  
	final int rating;
	
    WINDOWS(8),
    MAC(2),
    LINUX(9),
    OTHER(10);  
	
    public static OS determine() {  
        OS out = OTHER;  
        String myOS = System.getProperty("os.name").toLowerCase();  
        if (myOS.contains("win")) {  
            out = WINDOWS;  
        }  
        else if (myOS.contains("mac")) {  
            out = MAC;  
        } else if (myOS.contains("nux")) {  
            out = LINUX;  
        }  
        return out;  
    }  
}

public static void main(String[] args) {
	OS systemOS = OS.determine();
	System.out.println(systemOS);
}

```