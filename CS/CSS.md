# Flexbox vs Grid layout
https://youtu.be/wsTv9y931o8
https://youtu.be/hs3piaN4b5I
https://youtu.be/JYfiaSKeYhE


Flexbox is one dimensional. Elements are lined up horizontally one after another to infinity. But, because we have limited space in a web page, we can wrap that line, in other words break it into multiple lines. 
![[Pasted image 20251015121322.png|200]]

Grid is two dimensional 
![[Pasted image 20251015121616.png|200]]
Each area between the dotted lines is a *grid area*

## Bento grid
Named after Japanese food trays, we can control if an item can span over multiple grid areas. 
We can give each item in the grid a name. This is usually gone inline html:
```html
<div class="grid-container">
	<div class="box" style="grid-area: box-1"/>
	<div class="box" style="grid-area: box-2"/>
	<div class="box" style="grid-area: box-3"/>
	<div class="box" style="grid-area: box-4"/>
</div>
```
Otherwise we have to create a CSS class for each item to give it a grid name.  So this saves us from having to line more lines of code.

We can then control which box goes into which grid area.
```css
.grid-container {
	display: grid;
	grid-template-columns: 200px 200px 200px 200px;
	gap: 1em;
	grid-template-areas:
		/*each string corresponds to each row*/
		"box-1 box-2 box-2 box-3"
		"box-1 box-4 box-5 box-5";
}
```

We can then use [[CSS#Media query|media queries]] to change the grid layout (columns and in which grid areas the boxes go)
```css
@media screen and (max-width: 56em) {
	.grid-container{
		grid-template-columns: 200px 200px ;
		grid-template-areas:
		/*each string corresponds to each row*/
		"box-1 box-1 box-2"
		"box-1 box-1 box-3"
		"box-4 box-5 box-5";
	}
}
```
# Padding vs. Margin
Padding is the space between the contents of an element and the borders of that element
Margin is the space between the borders of an element and the borders of the other elements

# Media query
We can use media queries to apply styles if certain conditions are met.
The most common of these conditions is the width of the screen. In the following example, the background color changes depending on the size of the screen:

```css
<style>
/* Default style for the largest screens (or screens wider than the second breakpoint) */
body {
  background-color: #33ccff; /* Light Blue */
  transition: background-color 1s ease; /* Smooth transition for color changes */
}

/* This applies when the screen width is 1024 pixels or less */
@media screen and (max-width: 1024px) {
  body {
    background-color: #ff9933; /* Orange */
  }
}

/* This applies when the screen width is 600 pixels or less */
@media screen and (max-width: 600px) {
  body {
    background-color: #cc33ff; /* Purple */
  }
}
```
The `max-width` condition is different than the `max-width` property applied to containers. 
The first one says the maximum acceptable width is 600px, for example. Anymore and the condition is false. *Note: in the example above, when the width is 400px for example, both media queries are applied, but the second one overrides the first. That's why the smaller max-width condition is at the bottom: the first query sets the color to orange, but the second one immediately sets the color to purple.*

Media queries override only the properties that are specifically listed under them. 
In the example above, the background color change transition stays unaffected when the screen size changes. You could say it gets *inherited*/it doesn't get overriden

# Position
- `static`: Default positioning on a webpage. Does not support `left`, `right`, `top`, or `bottom`.
- `relative`: just like static
- `fixed`: relative to viewport. Does not move when scrolling
- `absolute`: used for positioning nesting elements. positions are based on the most recent ancestor.



