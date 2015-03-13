
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison GLR parsers in C
   
      Copyright (C) 2002, 2003, 2004, 2005, 2006 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NAME = 258,
     STRING = 259,
     INTNUM = 260,
     BOOL = 261,
     APPROXNUM = 262,
     USERVAR = 263,
     ASSIGN = 264,
     OR = 265,
     XOR = 266,
     ANDOP = 267,
     REGEXP = 268,
     LIKE = 269,
     IS = 270,
     IN = 271,
     NOT = 272,
     BETWEEN = 273,
     COMPARISON = 274,
     SHIFT = 275,
     MOD = 276,
     UMINUS = 277,
     ADD = 278,
     ALL = 279,
     ALTER = 280,
     ANALYZE = 281,
     AND = 282,
     ANY = 283,
     APPEND = 284,
     AS = 285,
     ASC = 286,
     AUTO_INCREMENT = 287,
     BEFORE = 288,
     BIGINT = 289,
     BINARY = 290,
     BIT = 291,
     BLOB = 292,
     BOTH = 293,
     BY = 294,
     CALL = 295,
     CASCADE = 296,
     CASE = 297,
     CHANGE = 298,
     CHAR = 299,
     CHECK = 300,
     COLLATE = 301,
     COLUMN = 302,
     COMMENT = 303,
     CONDITION = 304,
     CONSTRAINT = 305,
     CONTINUE = 306,
     CONVERT = 307,
     CREATE = 308,
     CROSS = 309,
     CURRENT_DATE = 310,
     CURRENT_TIME = 311,
     CURRENT_TIMESTAMP = 312,
     CURRENT_USER = 313,
     CURSOR = 314,
     DATABASE = 315,
     DATABASES = 316,
     DATE = 317,
     DATETIME = 318,
     DAY_HOUR = 319,
     DAY = 320,
     DAY_MICROSECOND = 321,
     DAY_MINUTE = 322,
     DAY_SECOND = 323,
     DECIMAL = 324,
     DECLARE = 325,
     DEFAULT = 326,
     DELAYED = 327,
     DELETE = 328,
     DESC = 329,
     DESCRIBE = 330,
     DETERMINISTIC = 331,
     DISTINCT = 332,
     DISTINCTROW = 333,
     DIV = 334,
     DOUBLE = 335,
     DROP = 336,
     DUAL = 337,
     EACH = 338,
     ELSE = 339,
     ELSEIF = 340,
     ENCLOSED = 341,
     END = 342,
     ENUM = 343,
     ESCAPED = 344,
     EXISTS = 345,
     EXIT = 346,
     EXPLAIN = 347,
     FETCH = 348,
     FLOAT = 349,
     FOR = 350,
     FORCE = 351,
     FOREIGN = 352,
     FROM = 353,
     FULLTEXT = 354,
     GRANT = 355,
     GROUP = 356,
     HAVING = 357,
     HIGH_PRIORITY = 358,
     HOUR_MICROSECOND = 359,
     HOUR_MINUTE = 360,
     HOUR_SECOND = 361,
     IF = 362,
     IGNORE = 363,
     INDEX = 364,
     INFILE = 365,
     INNER = 366,
     INOUT = 367,
     INSENSITIVE = 368,
     INSERT = 369,
     INT = 370,
     INTEGER = 371,
     INTERVAL = 372,
     INTO = 373,
     ITERATE = 374,
     JOIN = 375,
     KEY = 376,
     KEYS = 377,
     KILL = 378,
     LEADING = 379,
     LEAVE = 380,
     LEFT = 381,
     LIMIT = 382,
     LINES = 383,
     LOAD = 384,
     LOCALTIME = 385,
     LOCALTIMESTAMP = 386,
     LOCK = 387,
     LONG = 388,
     LONGBLOB = 389,
     LONGTEXT = 390,
     LOOP = 391,
     LOW_PRIORITY = 392,
     MATCH = 393,
     MEDIUMBLOB = 394,
     MEDIUMINT = 395,
     MEDIUMTEXT = 396,
     MINUTE_MICROSECOND = 397,
     MINUTE_SECOND = 398,
     MODIFIES = 399,
     NATURAL = 400,
     NO_WRITE_TO_BINLOG = 401,
     NULLX = 402,
     NUMBER = 403,
     ON = 404,
     DUPLICATE = 405,
     OPTIMIZE = 406,
     OPTION = 407,
     OPTIONALLY = 408,
     ORDER = 409,
     OUT = 410,
     OUTER = 411,
     OUTFILE = 412,
     PARTITIONED = 413,
     PRECISION = 414,
     PRIMARY = 415,
     PROCEDURE = 416,
     PROJECTION = 417,
     PURGE = 418,
     QUICK = 419,
     QUARTER = 420,
     READ = 421,
     READS = 422,
     REAL = 423,
     REFERENCES = 424,
     RELEASE = 425,
     RENAME = 426,
     REPEAT = 427,
     REPLACE = 428,
     REQUIRE = 429,
     RESTRICT = 430,
     RETURN = 431,
     REVOKE = 432,
     RIGHT = 433,
     ROLLUP = 434,
     SAMPLE = 435,
     SCHEMA = 436,
     SCHEMAS = 437,
     SECOND_MICROSECOND = 438,
     SELECT = 439,
     SENSITIVE = 440,
     SEPARATOR = 441,
     SET = 442,
     SHOW = 443,
     SMALLINT = 444,
     SOME = 445,
     SONAME = 446,
     SPATIAL = 447,
     SPECIFIC = 448,
     SQL = 449,
     SQLEXCEPTION = 450,
     SQLSTATE = 451,
     SQLWARNING = 452,
     SQL_BIG_RESULT = 453,
     SQL_CALC_FOUND_ROWS = 454,
     SQL_SMALL_RESULT = 455,
     SSL = 456,
     STARTING = 457,
     STRAIGHT_JOIN = 458,
     TABLE = 459,
     TEMPORARY = 460,
     TEXT = 461,
     TERMINATED = 462,
     THEN = 463,
     TIME = 464,
     TIMESTAMP = 465,
     TINYBLOB = 466,
     TINYINT = 467,
     TINYTEXT = 468,
     TO = 469,
     TRAILING = 470,
     TRIGGER = 471,
     UNDO = 472,
     UNION = 473,
     UNIQUE = 474,
     UNLOCK = 475,
     UNSIGNED = 476,
     UPDATE = 477,
     USAGE = 478,
     USE = 479,
     USING = 480,
     UTC_DATE = 481,
     UTC_TIME = 482,
     UTC_TIMESTAMP = 483,
     VALUES = 484,
     VARBINARY = 485,
     VARCHAR = 486,
     VARYING = 487,
     WHEN = 488,
     WHERE = 489,
     WHILE = 490,
     WITH = 491,
     WRITE = 492,
     YEAR = 493,
     YEAR_MONTH = 494,
     ZEROFILL = 495,
     WEEK = 496,
     DO = 497,
     MAX_QUERIES_PER_HOUR = 498,
     MAX_UPDATES_PER_HOUR = 499,
     MAX_CONNECTIONS_PER_HOUR = 500,
     MAX_USER_CONNECTIONS = 501,
     USER = 502,
     TRUNCATE = 503,
     FAST = 504,
     MEDIUM = 505,
     EXTENDED = 506,
     CHANGED = 507,
     LEAVES = 508,
     MASTER = 509,
     QUERY = 510,
     CACHE = 511,
     SLAVE = 512,
     BEGINT = 513,
     COMMIT = 514,
     START = 515,
     TRANSACTION = 516,
     NO = 517,
     CHAIN = 518,
     AUTOCOMMIT = 519,
     SAVEPOINT = 520,
     ROLLBACK = 521,
     LOCAL = 522,
     TABLES = 523,
     ISOLATION = 524,
     LEVEL = 525,
     GLOBAL = 526,
     SESSION = 527,
     UNCOMMITTED = 528,
     COMMITTED = 529,
     REPEATABLE = 530,
     SERIALIZABLE = 531,
     IDENTIFIED = 532,
     PASSWORD = 533,
     PRIVILEGES = 534,
     BACKUP = 535,
     CHECKSUM = 536,
     REPAIR = 537,
     USE_FRM = 538,
     RESTORE = 539,
     CHARACTER = 540,
     COLLATION = 541,
     COLUMNS = 542,
     ENGINE = 543,
     LOGS = 544,
     STATUS = 545,
     STORAGE = 546,
     ENGINES = 547,
     ERRORS = 548,
     GRANTS = 549,
     INNODB = 550,
     PROCESSLIST = 551,
     TRIGGERS = 552,
     VARIABLES = 553,
     WARNINGS = 554,
     FLUSH = 555,
     HOSTS = 556,
     DES_KEY_FILE = 557,
     USER_RESOURCES = 558,
     CONNECTION = 559,
     RESET = 560,
     PREPARE = 561,
     DEALLOCATE = 562,
     EXECUTE = 563,
     WORK = 564,
     BTREE = 565,
     HASH = 566,
     BDB = 567,
     OPEN = 568,
     FULL = 569,
     FSUBSTRING = 570,
     FTRIM = 571,
     FDATE_ADD = 572,
     FDATE_SUB = 573,
     FCOUNT = 574,
     FUPPER = 575,
     FCAST = 576,
     FCOALESCE = 577,
     FCONVERT = 578,
     FSUM = 579,
     FAVG = 580,
     FMIN = 581,
     FMAX = 582
   };
#endif


#ifndef YYSTYPE
typedef union YYSTYPE
{

/* Line 2638 of glr.c  */
#line 47 "sql.ypp"

	int intval;		// no used ---4-28
	double floatval;	// no used ---4-28
	char *strval;
	int subtok;
	struct Node * ast_node;



/* Line 2638 of glr.c  */
#line 387 "sql.tab.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{

  int first_line;
  int first_column;
  int last_line;
  int last_column;

} YYLTYPE;
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



extern YYSTYPE yylval;

extern YYLTYPE yylloc;


