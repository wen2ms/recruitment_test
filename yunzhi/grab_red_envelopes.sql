-- 一个典型的抢红包系统设计的完整数据库表结构

CREATE TABLE users (
	id BIGINT PRIMARY KEY AUTO_INCREMENT,
	username VARCHAR(100) NOT NULL UNIQUE,
);

CREATE TABLE red_envelopes (
	id BIGINT PRIMARY KEY AUTO_INCREMENT,
	sender_id BIGINT NOT NULL,
	total_amount DECIMAL(10, 2) NOT NULL,
	total_count INT NOT NULL,
	created_time DATETIME DEFAULT CURRENT_TIMESTAMP,
	
	INDEX idx_red_evlp_sender_id (sender_id),
	INDEX idx_red_evlp_create_time (created_time)
);

CREATE TABLE packet (
	id BIGINT PRIMARY KEY AUTO_INCREMENT,
	envelop_id BIGINT NOT NULL,
	amount DECIMAL(10, 2) NOT NULL,
	is_grabbed TINYINT DEFAULT 0,
	grabbed_by BIGINT DEFAULT NULL,
	grabbed_time DATETIME DEFAULT NULL,

	INDEX idx_packet_evlp_id (envelop_id),
	INDEX idx_packet_grabbed_by (grabbed_by)
);

CREATE TABLE envelopes_record (
	id BIGINT PRIMARY KEY AUTO_INCREMENT,
	envelop_id BIGINT NOT NULL,
	user_id BIGINT NOT NULL,
	amount DECIMAL(10, 2) NOT NULL,
	grabbed_time DATETIME DEFAULT CURRENT_TIMESTAMP,
	
	UNIQUE INDEX idx_record_evlp_user (envelop_id, user_id),
	INDEX idx_record_evlp (envelop_id),
	INDEX idx_record_user (user_id)
);