project('yagni', 'c')

sources = files(
    'yagni/src/main.c'
)

executable('yagni', 
    sources: sources,
    install: true,
    install_tag: 'application',
    install_dir: '.'
)

install_subdir('yagni/assets', 
    install_dir: 'assets',
    install_tag: 'application',
    strip_directory: true
)