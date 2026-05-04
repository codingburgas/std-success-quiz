project('quiz', 'cpp', version: '0.1')
gtkmm_dep = dependency('gtkmm-4.0')
program_name = 'quiz'
cpp_sources = [ 'src/ui.cpp', 'src/main.cpp', 'src/quiz.cpp', 'src/utils.cpp', 'src/backend.cpp' ]
executable(program_name,
  cpp_sources,
  dependencies: gtkmm_dep
)
