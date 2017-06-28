st=>start: Start
op=>operation: Your Operation
sub=>subroutine: My Subroutine
cond=>condition: Yes or No?
io=>inputoutput: catch something...
e=>end: End

st->op->cond
cond(yes)->io->e
cond(no)->sub(right)->op