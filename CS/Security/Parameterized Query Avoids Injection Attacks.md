Suppose that somewhere in our a web application, we need contruct an SQL query that uses input from the user. We should never use user input (untrusted data) directly, as it can deliberately set up our SQL query to behave differently than intended. For example, consider the following:
```java
public static Data doSomething(Database database, string username, string password) {
	string query = "SELECT id, first_name, last_name, from " + database + "Where username = " + username + " and password = " + password;
	Data results = database.runQuery(query);
	return results;
}
```
If a user enters "fred--" for username, the `--` will comment out the password and user is granted access to the database.

We need to make sure anything the user enters is not executed as a command and saved into the database as data. Enter the concept of parametrized queries. In java, it is called prepared statements (class `PreparedStatement` from the `java.sql.PreparedStatement` module) with a syntax like the following:
```java
public static Data doSomething(Database database, String username, String password) {
	String query = "SELECT id, first_name, last_name, from ? Where username = ? and password = ?";
	PreparedStatement pstm = database.preparedStatement(query)
	pstm.setString(1, database);
	ptsm.setString(2, username);
	ptsm.setString(3, password);
	Data results = ptsm.executeQuery();
	return results;
}

```

It will created an "execution plan" in the database, so the database will know what to do with the incoming data. In fact, the queries run faster this way/
