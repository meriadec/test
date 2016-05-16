all: server client
	@/bin/rm -f cli srv
	@ln -s client/cli .
	@ln -s server/srv .

server:
	@make -C server

client:
	@make -C client

fclean:
	@$(MAKE) -C client $@
	@$(MAKE) -C server $@
	@/bin/rm -f cli srv

re: fclean all

.PHONY: clean fclean re server client
