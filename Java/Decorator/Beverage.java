/* Beverage.java
 */
 
public abstract class Beverage
{
	String description = "Unknown Beverage";
	
	public Beverage() {
	}
	
	public String getDescription() {
		return description;
	}
	
	public abstract double cost();
}