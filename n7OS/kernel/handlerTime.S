.text
# cette directive sert a rendre l'etiquette publique
    .globl handlerTime
# debut du traitant
handlerTime:
# sauvegarde des registres importants
    pushl %eax
    pushl %edx
    pushl %ecx
# appel a la fonction C realisant le traitant 
    call timeUpdate
# restauration des registres importants
    popl %ecx
    popl %edx
    popl %eax
# fin du traitant
    iret