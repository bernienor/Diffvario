
/**
\brief Processing of GPS-strings from the Nano logger (Via the V7)
\author Bernt Hustad Hembre
\see Nano dataport specification http://max.kellermann.name/download/xcsoar/devel/lxnav/nano%20dataport%20specification.pdf

**/



void process_NANO(char **sstr, File f);
void process_GPGGA(char **sstr, File f);
