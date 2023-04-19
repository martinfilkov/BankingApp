CREATE TABLE user_data (
  user_id SERIAL PRIMARY KEY,
  first_name TEXT NOT NULL,
  last_name TEXT NOT NULL,
  email TEXT NOT NULL UNIQUE,
  hashed_password TEXT NOT NULL,
  account_number TEXT NOT NULL UNIQUE,
  account_balance FLOAT NOT NULL DEFAULT 0
);

INSERT INTO user_data (first_name, last_name, email, hashed_password, account_number, account_balance) VALUES 
('John', 'Doe', 'johndoe@gmail.com', 'p@ssw0rd123', '0012345678', 2500.00),
('Jane', 'Smith', 'janesmith@yahoo.com', 'h3ll0w0rld!', '0056789123', 5000.00),
('Bob', 'Johnson', 'bjohnson@hotmail.com', 'qwertyuiop', '0090123456', 10000.00);

CREATE OR REPLACE FUNCTION register_user(
  p_first_name TEXT,
  p_last_name TEXT,
  p_email TEXT,
  p_password TEXT,
  p_account_number TEXT
)
RETURNS VOID
AS $$
BEGIN
  INSERT INTO user_data (first_name, last_name, email, hashed_password, account_number)
  VALUES (p_first_name, p_last_name, p_email, p_password, p_account_number);
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION login_user(
  p_email TEXT,
  p_password TEXT
)
RETURNS BOOLEAN
AS $$
BEGIN
  IF (SELECT 1 FROM user_data WHERE email = p_email AND hashed_password = p_password) THEN
  	RETURN TRUE;
  ELSE
  	RETURN FALSE;
  END IF;
END;
$$ LANGUAGE plpgsql;