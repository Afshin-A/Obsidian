This patten allows us to add behavior/methods to a class without modifying that class

We have two interfaces: `visitor` and `visitee`
The `visitee` has a method that accepts a `visitor`. This visitor contains new behavior

```c#
// Visitee
interface Museum
{
	void accept(Visitor visitor);
}

// 
interface MuseumVisitor
{
	void visitArtMuseum(ArtMuseum artMuseum);
}

// Concrete visitee class. It sends 
class ArtMuseum : Museum
{
	public void accept(MuseumVisitor museumVisitor)
	{
		museumVisitor.visitArtMuseum(this);
	}
}

class Describe : MuseumVisitor
{
	public void visitArtMuseum(ArtMuseum artMuseum) {}
}

```

<iframe width="560" height="315" src="https://www.youtube.com/embed/VZwQ5iUVXGo?si=HMqvouWnxMMFVIz2" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>


