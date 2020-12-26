interface ISideBarState {
  entries: {
    name: string,
    isSelected: boolean,
  }[],
}

export const SIDE_BAR: ISideBarState = {
  entries: [
    {
      name: 'Сменить настроение',
      isSelected: true,
    },
    {
      name: 'Редактирование профиля',
      isSelected: false,
    },
    {
      name: 'Сменить почту',
      isSelected: false,
    }
  ]
}

export const PPS_TEXT = {
  change_photo: 'Изменить фото профиля',
}
