void ft_exit(char **args, int *exit_status) {
    printf("exit\n");

    // 1. Handle non-numeric argument
    if (args[1] && !ft_isdigit(args[1])) {
        // Debug: Print the problematic argument
        printf("minishell: exit: '%s': numeric argument required\n", args[1]);
        *exit_status = 255;
        return (perror("minishell: exit: "), exit(1));
    }

    // 2. Handle too many arguments
    if (args_nbr(args) > 2) {
        printf("minishell: exit: too many arguments\n");
        *exit_status = 1;
        return (perror("minishell: exit: "), exit(1));
    }

    // 3. Handle no argument
    if (args_nbr(args) == 1) {
        *exit_status = 0;
        exit(0);
    }
    // 4. Handle numeric argument
    else {
        exit(ft_atoi(args[1]));
    }
}