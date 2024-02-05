## Placeholders
Can’t think of a term in your search? Replace it with the **\_** symbol

## Wildcards
```
*
```

## Ranges
This returns results in
```
Mazda 2020 … 2022
```

### Date Ranges
```
before: 2020-10-05
```

```
after: 2022-10-05
```


## Specific Sites

Use the `site:` keyword to force google to return results from specific sites. For example, the following query returns results only from Reddit:
```
the passage of time movie review site:reddit.com
```

Similarly, you can return use wildcards to return results from certain top-level domains:
```
universal product code site:*.edu searching in academic sources
```

  

**AROUND(****x****)** forces two words to appear next to each other in search result:

bert AROUND(1) ernie

  

wildcard operator: *****

  
## Exclusion Operator
Use `-` to  exclude a term from your search results. For example,
```
learn web development -javascript
```
  

  
## File Formats
searching for specific file formats:

**filetype:**pdf

No longer works for .mp3 files. But, as a workaround, we can search for the term “mp3” in urls

inurl:mp3

  

Google backs up websites. It is possible to access the cached version, even if the website is down:

**cache:**freecodecamp.org

  

**inurl:** inurl:mp3

“inurl:healthy eating  will return documents that mention the words ‘healthy’ in their URL, and mention the word ‘eating’ anywhere in the document.”

**allinurl:** all of the ensuing terms after the url must appear in the url of returned websites

**intitle:**

**allintitle:**

**intext:**

**allintext:**