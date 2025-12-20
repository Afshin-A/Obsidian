ideal for flexible object creation

You're a hiring manager (main program) that needs to hire people. You assign this task to the department leads (product): 
- Tech lead interviews for tech jobs, asking tech questions
- Marketing lead interviews for marketing jobs, asking marketing questions 
The manager (main) coordinates the interviews.

creator
product

```cs
public interface Interviewer // Product
{
	public void askQuestions();
}

public class TechInterviewer : Interviewer // Concrete product
{
	public override void askQuestions()
	{
	
	}
}

public class MarketingInterviewer : Interviewer // Concrete product
{
	public override void askQuestions()
	{
	
	}
}

public abstract class HiringManager // Creator
{
	private abstract Interviewer makeInterviewer();
	public void conductInterview() {
		Interviewer interviewer = makeInterviewer();
		interviewer.askQuestions();
	}
}

public class TechManager : HiringManager
{
	private Interviewer makeInterviewer()
	{
		return new TechInterviewer();
	}
}

public class MarketManager : HiringManager
{
	private Interviewer makeInterviewer()
	{
		return new MarketingInterviewer();
	}
}

public static void Main() {
	var _ = new TechManager().conductInterview();
	var _ = new MargetManager().conductInterview();
}

```