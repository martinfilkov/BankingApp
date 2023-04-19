CREATE OR REPLACE FUNCTION account_summary(p_email TEXT)
RETURNS TABLE (p_first_name TEXT, p_last_name TEXT, t_email TEXT, p_account_number TEXT, p_account_balance FLOAT)
AS $$
BEGIN
    RETURN QUERY SELECT first_name, last_name, email, account_number, account_balance 
                 FROM user_data WHERE email = p_email;
END;
$$
LANGUAGE plpgsql;








CREATE OR REPLACE FUNCTION deposit_funds(p_email TEXT, deposit FLOAT)
RETURNS TEXT AS $$
BEGIN
	IF (deposit > 5 AND deposit < 1000000) THEN
		UPDATE user_data
		SET account_balance = account_balance + deposit
		WHERE email = p_email;
		RETURN 'Successfuly deposited!';
	ELSE
		RETURN 'Deposit Failed! Deposit must be between 5$ and 1 000 000$!';
	END IF;
END;
$$
LANGUAGE plpgsql;














CREATE OR REPLACE FUNCTION send_funds(p_sender_email TEXT, p_recipient_number TEXT, funds FLOAT)
RETURNS TEXT AS $$
DECLARE
	p_sender_account_balance FLOAT;
	p_first_name_recipient TEXT;
	p_last_name_recipient TEXT;
BEGIN
	IF (SELECT 1 FROM user_data WHERE account_number = p_recipient_number) THEN
		SELECT user_data.account_balance INTO p_sender_account_balance
		FROM user_data
		WHERE email = p_sender_email;

		SELECT user_data.first_name INTO p_first_name_recipient
		FROM user_data
		WHERE account_number = p_recipient_number;
		
		SELECT user_data.last_name INTO p_last_name_recipient
		FROM user_data
		WHERE account_number = p_recipient_number;

		IF (p_sender_account_balance - funds) > 0 THEN
			UPDATE user_data
			SET account_balance = account_balance - funds
			WHERE email = p_sender_email;

			UPDATE user_data
			SET account_balance = account_balance + funds
			WHERE account_number = p_recipient_number;

			RETURN 'Successfuly sent ' || funds::text || '$ to account number: ' || p_recipient_number || '(' || p_first_name_recipient || ' ' || p_last_name_recipient || ')';
			
		ELSE
			RETURN 'You dont have enough balance!';
		END IF;
	ELSE
		RETURN 'User in our system with account_number "' || p_recipient_number || '" was not found!';
	END IF;
END;
$$
LANGUAGE plpgsql;